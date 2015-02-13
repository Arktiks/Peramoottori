#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

class Image
{
public:
	Image();
	Image(std::string fileName);
	Image(std::vector<unsigned char> pixels);

	//bool LoadFromFile(std::string fileName);

	~Image() {};

private:
	unsigned int width;
	unsigned int height;
	std::vector<unsigned char> pixels;
};

#endif