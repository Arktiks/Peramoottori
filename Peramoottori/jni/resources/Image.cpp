#include "Image.h"
#include <resources\ResourceReader.h>

Image::Image() : width(0), height(0)
{
}

Image::Image(std::string fileName) : width(0), height(0)
{
}

Image::Image(std::vector<unsigned char> pixels) : width(0), height(0), pixels(pixels)
{
}

/*bool Image::LoadFromFile(std::string fileName)
{
	ResourceReader* tempReader = ResourceReader::GetInstance();
	pixels = tempReader->ReadImage(fileName);
	
}*/