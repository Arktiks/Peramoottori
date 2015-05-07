#include "TextureFactory.h"
#include <resources\ResourceManager.h>
#include <resources\ImageResource.h>

#include <core\Log.h>
#include <core\Memory.h>
#include <GLES2\gl2.h>

#include <lodepng.h>

std::map<std::string, pm::Texture*> pm::TextureFactory::generatedTextures = { { "MapInit", nullptr } };

pm::Texture* pm::TextureFactory::CreateTexture(std::string fileName)
{
	for (std::map<std::string, Texture*>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
	{
		if (it->first == fileName)
		{
			return it->second;
		}
	}

	pm::Texture* tempTexture = NEW pm::Texture;
	CreateOGLTexture(fileName, tempTexture);
	generatedTextures[fileName] = tempTexture;

	return tempTexture;
	
}

void pm::TextureFactory::CreateOGLTexture(std::string fileName, Texture* pointer)
{
	pm::ImageResource* decodedImage = (pm::ImageResource*)pm::ResourceManager::GetInstance()->LoadAsset(fileName);

	std::vector<unsigned char> img;
	unsigned int sx = 0;
	unsigned int sy = 0;

	unsigned error = lodepng::decode(img, sx, sy, decodedImage->GetImageData().data(), decodedImage->GetImageData().size());

	if (error) // display error to debugger;
	{
		DEBUG_WARNING(("Texture Creation failed lodepng error #%u", error));
		return;
	}
	else
	{
		GLuint textureIndex;
		glGenTextures(1, &textureIndex);
		glBindTexture(GL_TEXTURE_2D, textureIndex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			sx, sy,
			0, GL_RGBA, GL_UNSIGNED_BYTE,
			img.data());

		glBindTexture(GL_TEXTURE_2D, 0);

		DEBUG_GL_ERROR();

		pointer->SetTextureSize(glm::uvec2(sx, sy));
		pointer->SetId(textureIndex);
	}
}

void pm::TextureFactory::RecreateOGLTextures()
{
	for (std::map<std::string, Texture*>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
	{
		CreateOGLTexture(it->first, it->second);
	}
}

void pm::TextureFactory::DestroyOGLTextures()
{
	for (std::map<std::string, Texture*>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
	{
		GLuint asd = it->second->GetId();
		glDeleteTextures(1, &asd);
	}
}

pm::TextureFactory::~TextureFactory()
{
	for (std::map<std::string, Texture*>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
	{
		GLuint asd = it->second->GetId();
		glDeleteTextures(1, &asd);
		delete it->second;
		it->second = nullptr;
	}
	generatedTextures.clear();
}

