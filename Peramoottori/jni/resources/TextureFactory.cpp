#include "TextureFactory.h"
#include <resources\ResourceManager.h>
#include <resources\ImageResource.h>

#include <core\Log.h>
#include <core\Memory.h>
#include <GLES2\gl2.h>


#include <lodepng.h>
#include <graphics\Text.h>

pm::SavedTextureStruct TS;
std::map<std::string, pm::SavedTextureStruct> pm::TextureFactory::generatedTextures = { { "MapInit", TS } };

pm::Texture* pm::TextureFactory::CreateTexture(std::string fileName)
{
	pm::Texture* tempTexture = NEW pm::Texture;

	for (std::map<std::string, pm::SavedTextureStruct>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
	{
		if (it->first == fileName)
		{
			tempTexture->SetId(&it->second.textureIndex);
			tempTexture->SetTextureSize(glm::uvec2((it->second.sizeX), (it->second.sizeY)));
			tempTexture->SetTrueSize(glm::uvec2((it->second.trueSizeX), (it->second.trueSizeY)));
			return tempTexture;
		}
	}

	pm::SavedTextureStruct tempSavedTextureStruct;

	CreateOGLTexture(fileName, &tempSavedTextureStruct);
	generatedTextures[fileName] = tempSavedTextureStruct;

	tempTexture->SetId(&tempSavedTextureStruct.textureIndex);
	tempTexture->SetTextureSize(glm::vec2(tempSavedTextureStruct.sizeX, tempSavedTextureStruct.sizeY));
	tempTexture->SetTrueSize(glm::vec2(tempSavedTextureStruct.trueSizeX, tempSavedTextureStruct.trueSizeY));
	
	if (tempSavedTextureStruct.translucent)
		tempTexture->SetTranslucency(pm::Texture::TRANSLUCENT);
	else
		tempTexture->SetTranslucency(pm::Texture::OPAQUE);
	
	return tempTexture;
}

void pm::TextureFactory::CreateOGLTexture(std::string fileName, pm::SavedTextureStruct* TextureStruct)
{
	if (fileName.empty() || fileName == "MapInit")
	{
		DEBUG_WARNING(("TextureFactory failed to create texture (%s).", fileName.c_str()));
		return;
	}

	// LOADFILE AND CREATE IMAGE

	DEBUG_GL_ERROR_CLEAR();
	pm::ImageResource* decodedImage = (pm::ImageResource*)pm::ResourceManager::GetInstance()->LoadAsset(fileName);

	std::vector<unsigned char> image;
	unsigned int sizeX = 0;
	unsigned int sizeY = 0;

	unsigned error = lodepng::decode(image, sizeX, sizeY, decodedImage->GetImageData().data(), decodedImage->GetImageData().size());

	if (error) // display error to debugger
	{
		DEBUG_WARNING(("Texture Creation failed lodepng error #%u", error));
		return;
	}
	
	// LOADFILE AND CREATE IMAGE

	// Create storage for parameters
	bool translucent;

	unsigned int xPowerOfTwo;
	unsigned int yPowerOfTwo;
	
	// Check if the texture needs padding to reach next power of two.
	DoPowerOfTwoStuff(&image, &xPowerOfTwo, &yPowerOfTwo, &translucent, sizeX, sizeY);

	// Create opengl texture, and return textureIndex of the texture
	GLuint textureIndex = CreateOpenGLTexture(xPowerOfTwo, yPowerOfTwo, &image);

	TextureStruct->sizeX = xPowerOfTwo;
	TextureStruct->sizeY = yPowerOfTwo;
	TextureStruct->trueSizeX = sizeX;
	TextureStruct->trueSizeY = sizeY;
	TextureStruct->textureIndex = textureIndex;
	TextureStruct->translucent = translucent;
}

void pm::TextureFactory::ReCreateOGLTexture(std::string fileName, pm::SavedTextureStruct* tempTS)
{
	if (fileName.empty() || fileName == "MapInit")
	{
		DEBUG_WARNING(("TextureFactory failed to create texture (%s).", fileName.c_str()));
		return;
	}

	// LOADFILE AND CREATE IMAGE

	DEBUG_GL_ERROR_CLEAR();
	pm::ImageResource* decodedImage = (pm::ImageResource*)pm::ResourceManager::GetInstance()->LoadAsset(fileName);

	std::vector<unsigned char> image;
	unsigned int sizeX = 0;
	unsigned int sizeY = 0;

	unsigned error = lodepng::decode(image, sizeX, sizeY, decodedImage->GetImageData().data(), decodedImage->GetImageData().size());

	if (error) // display error to debugger
	{
		DEBUG_WARNING(("Texture Creation failed lodepng error #%u", error));
		return;
	}

	// LOADFILE AND CREATE IMAGE

	// Create storage for parameters
	unsigned int xPowerOfTwo, yPowerOfTwo;
	bool translucent;

	// Check if the texture needs padding to reach next power of two.
	DoPowerOfTwoStuff(&image, &xPowerOfTwo, &yPowerOfTwo, &translucent, sizeX, sizeY);
	
	// Create opengl texture, and return textureIndex of the texture
	GLuint textureIndex = CreateOpenGLTexture(xPowerOfTwo, yPowerOfTwo, &image);

	tempTS->textureIndex = textureIndex;
	tempTS->sizeX = xPowerOfTwo;
	tempTS->sizeY = yPowerOfTwo;
	tempTS->trueSizeX = sizeX;
	tempTS->trueSizeY = sizeY;
		
}

void pm::TextureFactory::DoPowerOfTwoStuff(std::vector<unsigned char>* imagePointer, unsigned int* xPowerOfTwo, unsigned int* yPowerOfTwo,
	bool* translucent, uint sizeX, uint sizeY)
{
	bool tempPowerOfTwo = true;
	bool tempTranslucent = false;

	unsigned int tempXPowerOfTwo = 2, tempYPowerOfTwo = 2;
	while (tempXPowerOfTwo < sizeX)
		tempXPowerOfTwo *= 2;

	if (tempXPowerOfTwo != sizeX)
	{
		tempPowerOfTwo = false;
		tempTranslucent = true;
	}

	while (tempYPowerOfTwo < sizeY)
		tempYPowerOfTwo *= 2;

	if (tempYPowerOfTwo != sizeY)
	{
		tempPowerOfTwo = false;
		tempTranslucent = true;
	}


	std::vector<unsigned char>::iterator it;

	for (int y = 0; y < tempYPowerOfTwo; y++)
	{
		if (y < sizeY)
		{
			it = imagePointer->begin() + (sizeX + (y * tempXPowerOfTwo)) * 4;

			std::vector<unsigned char> fillerVec((tempXPowerOfTwo - sizeX) * 4, 0);

			imagePointer->insert(it, fillerVec.begin(), fillerVec.end());
		}
		else
		{
			it = imagePointer->end();

			std::vector<unsigned char> fillerVec(tempXPowerOfTwo * 4, 0);

			imagePointer->insert(it, fillerVec.begin(), fillerVec.end());
		}
	}

	if (tempPowerOfTwo)
	{
		for (int i = 0; i < imagePointer->size() / 4; i++)
		{
			if ((*imagePointer)[i * 4 + 3] < 255)
			{
				tempTranslucent = true;
				break;
			}
		}
	}
	*xPowerOfTwo = tempXPowerOfTwo;
	*yPowerOfTwo = tempYPowerOfTwo;
	*translucent = tempTranslucent;

}

GLuint pm::TextureFactory::CreateOpenGLTexture(unsigned int xPowerOfTwo,
	unsigned int yPowerOfTwo, std::vector<unsigned char>* imagePointer)
{

	GLuint tempTextureIndex;
	glGenTextures(1, &tempTextureIndex);
	DEBUG_GL_ERROR();

	glBindTexture(GL_TEXTURE_2D, tempTextureIndex);
	DEBUG_GL_ERROR();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	DEBUG_GL_ERROR();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	DEBUG_GL_ERROR();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		xPowerOfTwo, yPowerOfTwo,
		0, GL_RGBA, GL_UNSIGNED_BYTE,
		imagePointer->data());

	DEBUG_GL_ERROR();

	glBindTexture(GL_TEXTURE_2D, 0);
	DEBUG_GL_ERROR();

	return tempTextureIndex;

}

void pm::TextureFactory::RemoveTextureGroup(uint textureGroupToRemove)
{
	for (std::map<std::string, pm::SavedTextureStruct>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
	{
		if (it->second.textureGroup == textureGroupToRemove)
		{
			ResourceManager::GetInstance()->DeleteResource(it->first);
			it = generatedTextures.erase(it);
		}
	}
}

void pm::TextureFactory::RemoveTexture(std::string path)
{
	std::map<std::string, pm::SavedTextureStruct>::iterator it = generatedTextures.find(path);
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
		std::map<std::string, pm::SavedTextureStruct>::iterator it;
		for (it = generatedTextures.begin(); it != generatedTextures.end(); it++)
		{
			ReCreateOGLTexture(it->first, &it->second);
		}
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
	for (std::map<std::string, pm::SavedTextureStruct>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
	{
		GLuint reference = it->second.textureIndex;
		glDeleteTextures(1, &reference);
		DEBUG_GL_ERROR();
		//delete it->second;
		//it->second = nullptr;
	}
	generatedTextures.clear();
}