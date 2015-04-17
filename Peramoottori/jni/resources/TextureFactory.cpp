#include "TextureFactory.h"
#include "resources\ResourceManager.h"
#include "ImageResource.h"
#include <lodepng.h>
#include <core\Memory.h>

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


	pm::ImageResource* decodedImage = (pm::ImageResource*)pm::ResourceManager::GetInstance()->LoadAsset(fileName);


	std::vector<unsigned char> img;
	
	unsigned int sx = 0;
	unsigned int sy = 0;

	unsigned error = lodepng::decode(img, sx, sy, decodedImage->GetImageData().data(), decodedImage->GetImageData().size());

	if (error) // display error to debugger;
	{
		DEBUG_WARNING(("Texture Creation failed lodepng error #%u", error));
		return nullptr;
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

		pm::Texture* tempTexture = NEW pm::Texture;
		tempTexture->SetTextureSize(glm::uvec2(sx, sy));
		tempTexture->SetId(textureIndex);

		DEBUG_GL_ERROR();

		generatedTextures[fileName] = tempTexture;

		return tempTexture;
	}

	
}

pm::TextureFactory::~TextureFactory()
{
	for (std::map<std::string, Texture*>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
	{
		delete it->second;
	}
	generatedTextures.clear();
}