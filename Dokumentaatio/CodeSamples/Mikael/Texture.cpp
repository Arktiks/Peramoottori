#include "Texture.h"

using namespace PORT;

Texture::Texture(std::string filePath)
{
	std::vector<unsigned char> image;
#if defined WIN32
	lodepng::decode(image, width, height, filePath);

#elif defined ANDROID
	std::string data = FileLoader::getInstance()->loadFile(filePath);
	LOG("data length %i" , data.length());
	std::vector<unsigned char> dataVec;
	for (int i = 0; i < data.length(); i++)
	{
		dataVec.push_back(data[i]);
	}


	unsigned error = lodepng::decode(image, width, height, dataVec);
	
	LOG("%u width %u height %u %u", error,width, height, dataVec.size());

#endif


	glGenTextures(1, &index);

	glBindTexture(GL_TEXTURE_2D, index);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0u);
}