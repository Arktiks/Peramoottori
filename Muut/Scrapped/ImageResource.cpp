#include "ImageResource.h"



pm::ImageResource::ImageResource()
{
}

pm::ImageResource::ImageResource(std::vector<unsigned char> pixels) : imageData(pixels) {}

std::vector <unsigned char> pm::ImageResource::GetImageData()
{
	return imageData;
}

pm::ImageResource::~ImageResource()
{
}
