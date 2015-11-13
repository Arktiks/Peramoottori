#include "TextureFactory.h"
#include <resources\ResourceManager.h>
#include <resources\ImageResource.h>

#include <core\Log.h>
#include <core\Memory.h>
#include <GLES2\gl2.h>


#include <lodepng.h>
#include <graphics\Text.h>

pm::TextureStruct TS;
std::map<std::string, pm::TextureStruct> pm::TextureFactory::generatedTextures = { { "MapInit", TS } };

pm::Texture* pm::TextureFactory::CreateTexture(std::string fileName)
{
	
	pm::Texture* tempTexture = NEW pm::Texture;

	for (std::map<std::string, pm::TextureStruct>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
	{
		if (it->first == fileName)
		{
			tempTexture->SetId(it->second.ti);
			tempTexture->SetTextureSize(glm::uvec2((it->second.sx), (it->second.sy)));
			tempTexture->SetTrueSize(glm::uvec2((it->second.tsx), (it->second.tsy)));
			return tempTexture;
		}
	}


	CreateOGLTexture(fileName, tempTexture);

	pm::TextureStruct tempTS;// = (pm::TextureStruct*)malloc(sizeof(*tempTS));

	tempTS.ti = tempTexture->GetId();
	tempTS.sx = (uint)tempTexture->GetTextureSize().x;
	tempTS.sy = (uint)tempTexture->GetTextureSize().y;
	tempTS.tsx = (uint)tempTexture->GetTrueSize().x;
	tempTS.tsy = (uint)tempTexture->GetTrueSize().y;

	generatedTextures[fileName] = tempTS;

	return tempTexture;
}

void pm::TextureFactory::CreateOGLTexture(std::string fileName, Texture* pointer)
{
	if (fileName.empty() || pointer == nullptr)
	{
		DEBUG_WARNING(("TextureFactory failed to create texture (%s).", fileName.c_str()));
		return;
	}

	DEBUG_GL_ERROR_CLEAR();
	pm::ImageResource* decodedImage = (pm::ImageResource*)pm::ResourceManager::GetInstance()->LoadAsset(fileName);

	std::vector<unsigned char> image;
	unsigned int sizex = 0;
	unsigned int sizey = 0;

	unsigned error = lodepng::decode(image, sizex, sizey, decodedImage->GetImageData().data(), decodedImage->GetImageData().size());

	if (error) // display error to debugger
	{
		DEBUG_WARNING(("Texture Creation failed lodepng error #%u", error));
		return;
	}
	else
	{

		unsigned int xpo2 = 2;
		while (xpo2 < sizex)
			xpo2 *= 2;

		unsigned int ypo2 = 2;
		while (ypo2 < sizey)
			ypo2 *= 2;

		std::vector<unsigned char>::iterator it;

		for (int y = 0; y < ypo2; y++)
		{
			if (y < sizey)
			{
				it = image.begin() + (sizex + (y * xpo2)) * 4;

				std::vector<unsigned char> fillerVec((xpo2 - sizex) * 4, 0);
				
				image.insert(it, fillerVec.begin(), fillerVec.end());
			}
			else
			{
				it = image.end();

				std::vector<unsigned char> fillerVec(xpo2 * 4, 0);

				image.insert(it, fillerVec.begin(), fillerVec.end());
			}
		}
		
		GLuint textureIndex;
		glGenTextures(1, &textureIndex);
		DEBUG_GL_ERROR();

		glBindTexture(GL_TEXTURE_2D, textureIndex);
		DEBUG_GL_ERROR();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		DEBUG_GL_ERROR();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		DEBUG_GL_ERROR();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			xpo2, ypo2,
			0, GL_RGBA, GL_UNSIGNED_BYTE,
			image.data());
		DEBUG_GL_ERROR();

		glBindTexture(GL_TEXTURE_2D, 0);
		DEBUG_GL_ERROR();

		pointer->SetTextureSize(glm::uvec2(xpo2, ypo2));
		pointer->SetTrueSize(glm::uvec2(sizex, sizey));
		pointer->SetId(textureIndex);
	}
}

void pm::TextureFactory::CreateOGLTexture(std::string fileName, pm::TextureStruct tempTS)
{
	if (fileName.empty() || fileName == "MapInit")
	{
		DEBUG_WARNING(("TextureFactory failed to create texture (%s).", fileName.c_str()));
		return;
	}

	DEBUG_GL_ERROR_CLEAR();
	pm::ImageResource* decodedImage = (pm::ImageResource*)pm::ResourceManager::GetInstance()->LoadAsset(fileName);

	std::vector<unsigned char> image;
	unsigned int sizex = 0;
	unsigned int sizey = 0;

	unsigned error = lodepng::decode(image, sizex, sizey, decodedImage->GetImageData().data(), decodedImage->GetImageData().size());

	if (error) // display error to debugger
	{
		DEBUG_WARNING(("Texture Creation failed lodepng error #%u", error));
		return;
	}
	else
	{

		unsigned int xpo2 = 2;
		while (xpo2 < sizex)
			xpo2 *= 2;

		unsigned int ypo2 = 2;
		while (ypo2 < sizey)
			ypo2 *= 2;

		std::vector<unsigned char>::iterator it;

		for (int y = 0; y < ypo2; y++)
		{
			if (y < sizey)
			{
				it = image.begin() + (sizex + (y * xpo2)) * 4;

				std::vector<unsigned char> fillerVec((xpo2 - sizex) * 4, 0);

				image.insert(it, fillerVec.begin(), fillerVec.end());
			}
			else
			{
				it = image.end();

				std::vector<unsigned char> fillerVec(xpo2 * 4, 0);

				image.insert(it, fillerVec.begin(), fillerVec.end());
			}
		}

		GLuint textureIndex;
		glGenTextures(1, &textureIndex);
		DEBUG_GL_ERROR();

		glBindTexture(GL_TEXTURE_2D, textureIndex);
		DEBUG_GL_ERROR();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		DEBUG_GL_ERROR();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		DEBUG_GL_ERROR();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			xpo2, ypo2,
			0, GL_RGBA, GL_UNSIGNED_BYTE,
			image.data());
		DEBUG_GL_ERROR();

		glBindTexture(GL_TEXTURE_2D, 0);
		DEBUG_GL_ERROR();

		tempTS.sx = xpo2;
		tempTS.sy = ypo2;
		tempTS.tsx = sizex;
		tempTS.tsy = sizey;
		tempTS.ti = textureIndex;
	}
}

void pm::TextureFactory::RemoveTextureGroup(uint textureGroupToRemove)
{
	for (std::map<std::string, pm::TextureStruct>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
	{
		if (it->second.tg == textureGroupToRemove)
		{
			ResourceManager::GetInstance()->DeleteResource(it->first);
			it = generatedTextures.erase(it);
		}
	}
}

void pm::TextureFactory::RemoveTexture(std::string path)
{
	std::map<std::string, pm::TextureStruct>::iterator it = generatedTextures.find(path);
	if (it != generatedTextures.end())
	{
		ResourceManager::GetInstance()->DeleteResource(it->first);
		it = generatedTextures.erase(it);
	}
}

void pm::TextureFactory::RecreateOGLTextures()
{
	if (!generatedTextures.empty())
	{
		for (std::map<std::string, pm::TextureStruct>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
			CreateOGLTexture(it->first, it->second);
	}
}

						
void pm::TextureFactory::DestroyOGLTextures()
{

	DEBUG_GL_ERROR_CLEAR();

	// Small request to make this a functional function

	/*
	for (std::map<std::string, Texture*>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
	{
		glDeleteTextures(1, &it->second->GetId());
		DEBUG_GL_ERROR();
	}*/

	/*
	for (GLuint i = 0; i < generatedTextures.size(); i++) // Bubblegum fix temporary!
	{
		glDeleteTextures(1, &i);
		DEBUG_GL_ERROR();
	}
	*/
}

pm::TextureFactory::~TextureFactory()
{
	DEBUG_GL_ERROR_CLEAR();
	for (std::map<std::string, pm::TextureStruct>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
	{
		GLuint reference = it->second.ti;
		glDeleteTextures(1, &reference);
		DEBUG_GL_ERROR();
		//delete it->second;
		//it->second = nullptr;
	}
	generatedTextures.clear();
}