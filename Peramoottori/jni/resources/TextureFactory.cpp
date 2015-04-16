#include "TextureFactory.h"
#include "resources\ResourceManager.h"
#include <lodepng.h>

pm::Texture TextureFactory::CreateTexture(std::string fileName)
{
	pm::Texture tempTexture;

	pm::ImageResource* decodedImage = (pm::ImageResource*)pm::ResourceManager::GetInstance()->LoadAsset(fileName);

	glm::vec2 asd;

	std::vector<unsigned char> Image;
	
	unsigned error = lodepng::decode(Image, asd.x, asd.y, decodedImage->getImageData());
	

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
			asd.x, asd.y,
			0, GL_RGBA, GL_UNSIGNED_BYTE,
			Image.data());

		return tempTexture;
	}

	
}
