#include "TextureFactory.h"
#include "resources\ResourceManager.h"
#include "ImageResource.h"
#include <lodepng.h>

pm::Texture* TextureFactory::CreateTexture(std::string fileName)
{
	pm::Texture* tempTexture = new pm::Texture;

	pm::ImageResource* decodedImage = (pm::ImageResource*)pm::ResourceManager::GetInstance()->LoadAsset(fileName);


	std::vector<unsigned char> img;
	
	unsigned int sx = 0;
	unsigned int sy = 0;
	unsigned char* data;
	int dataSize;
	lodepng::State pngState;
	unsigned error = lodepng::decode(img, sx, sy, pngState, decodedImage->GetImageData().data(), decodedImage->GetImageData().size());

	if (error) // display error to debugger;
	{
		DEBUG_WARNING(("Texture Creation failed"));
	}
	else
	{
		GLuint textureIndex;
		glGenTextures(1, &textureIndex);
		glBindTexture(GL_TEXTURE_2D, textureIndex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			sx, sy,
			0, GL_RGBA, GL_UNSIGNED_BYTE,
			img.data());
		tempTexture->SetTextureSize(glm::uvec2(sx, sy));
		tempTexture->SetId(textureIndex);
		return tempTexture;
	}

	
}
