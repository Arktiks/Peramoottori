#include "Texture.h"
using namespace pm;

Texture::Texture()
{	
}

Texture::Texture(std::string fileName)
{
	createTexture(fileName);
}

Texture::~Texture()
{
}

void Texture::createTexture(std::string fileName) // Nimeämiset
{
	pm::Image image = LoadImage(fileName);
	std::vector<unsigned char> decodedImage = DecodePNG(image);
	GenerateTexture(decodedImage);
}
pm::Image Texture::LoadImage(std::string fileName)
{
	pm::Image image = pm::ResourceManager::GetInstance()->ReadImage(fileName);
	return image;
}
std::vector<unsigned char> Texture::DecodePNG(pm::Image image)
{
	std::vector<unsigned char> decodedImage;
	
	unsigned error = lodepng::decode(decodedImage, textureSize.x, textureSize.y, image.pixels);
	

	if (error) // display error to debugger;
	{
	}
	else
	return decodedImage;
	
}

void Texture::GenerateTexture(std::vector<unsigned char> decodedImage)
{

	GLuint errorrs = 0;
	errorrs = glGetError();
	if (errorrs != 0)
		DEBUG_INFO((" 1 %d", errorrs));

	glEnable(GL_TEXTURE_2D);
	errorrs = glGetError();
	DEBUG_INFO((" glEnable %d", errorrs));

	glGenTextures(1, &textureIndex);
	errorrs = glGetError();
	if (errorrs != 0)
		DEBUG_INFO((" 2 %d", errorrs));

	glBindTexture(GL_TEXTURE_2D, textureIndex);

	errorrs = glGetError();

	if (errorrs != 0)
		DEBUG_INFO(("3 %d", errorrs));

	uint32_t data[2][2] = 
	{
		0xff0000ff, 0x00ff00ff,
		0x0000ffff, 0xff0000ff
	};

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
	//	2, 2,//textureSize.x, textureSize.y,
	//	0, GL_RGBA, GL_UNSIGNED_BYTE,
	//	data);//decodedImage.data());

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		textureSize.x, textureSize.y,
		0, GL_RGBA, GL_UNSIGNED_BYTE,
		decodedImage.data());

	errorrs = glGetError();
	if (errorrs != 0)
		DEBUG_INFO(("4 %d", errorrs));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0u);
}

GLuint Texture::getId()
{
	return textureIndex;
}
glm::vec2 Texture::getTextureSize()
{
	return textureSize;
}