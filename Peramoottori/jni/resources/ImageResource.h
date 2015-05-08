#ifndef IMAGERESOURCE_H
#define IMAGERESOURCE_H

#include <resources\Resource.h>
#include <vector>

namespace pm
{
	class ImageResource : public Resource
	{
	public:
		ImageResource();
		///constructor
		ImageResource(std::vector<unsigned char> pixels) :
			imageData(pixels) {};
		/// returns image data 
		std::vector <unsigned char> GetImageData() { return imageData; }

		~ImageResource() {};

	private:

		std::vector <unsigned char> imageData;

	};
}

#endif //!IMAGERESOURCE_H