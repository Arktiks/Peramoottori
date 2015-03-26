#include "Texture.h"


pm::Texture::Texture()
{	
}

pm::Texture::Texture(std::string fileName)
{
	createTexture(fileName);
}

pm::Texture::~Texture()
{
}

void pm::Texture::createTexture(std::string fileName) // Nimeämiset
{
	pm::Image image = LoadImage(fileName);
	std::vector<unsigned char> decodedImage = DecodePNG(image);
	GenerateTexture(decodedImage);
}
pm::Image pm::Texture::LoadImage(std::string fileName)
{
	pm::Image image = pm::ResourceManager::GetInstance()->ReadImage(fileName);
	return image;
}
std::vector<unsigned char> pm::Texture::DecodePNG(pm::Image image)
{
	std::vector<unsigned char> decodedImage;
	
	unsigned error = lodepng::decode(decodedImage, textureSize.x, textureSize.y, image.pixels);
	

	if (error) // display error to debugger;
	{
	}
	else
	return decodedImage;
	
}

void pm::Texture::GenerateTexture(std::vector<unsigned char> decodedImage)
{
	glGenTextures(1, &textureIndex);
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		textureSize.x, textureSize.y,
		0, GL_RGBA, GL_UNSIGNED_BYTE,
		decodedImage.data());
}

GLuint pm::Texture::getId()
{
	return textureIndex;
}
glm::vec2 pm::Texture::getTextureSize()
{
	return textureSize;
}