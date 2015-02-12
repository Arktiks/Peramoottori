#ifndef LOADEDIMAGE_H
#define LOADEDIMAGE_H

#include <vector>

struct LoadedImage
{
public:
	unsigned int width;
	unsigned int height;
	std::vector<unsigned char> decodedImage;

	LoadedImage() : width(0), height(0) {};
	LoadedImage(std::vector<unsigned char> decodedImage, unsigned int width, unsigned int height)
		: width(width), height(height), decodedImage(decodedImage) {};
};

#endif