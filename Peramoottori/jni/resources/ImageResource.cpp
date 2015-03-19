#include "ImageResource.h"

using namespace pm;

ImageResource::ImageResource()
{
}

ImageResource::ImageResource(std::vector<unsigned char> pixels) : imageData(pixels) {}

std::vector <unsigned char> ImageResource::getImageData()
{
	return imageData;
}

ImageResource::~ImageResource()
{
}
