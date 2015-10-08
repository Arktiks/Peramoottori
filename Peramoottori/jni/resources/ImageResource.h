#ifndef IMAGERESOURCE_H
#define IMAGERESOURCE_H

#include <resources\Resource.h>
#include <vector>

namespace pm
{

	/** \brief
	*
	* Long description.
	*
	* \ingroup Resources
	*/

	class ImageResource : public Resource
	{
	public:

		ImageResource() = delete;
		
		/** \brief
		*
		* \param[in] pixels Image data as unsigned char.
		*/
		ImageResource(std::vector<unsigned char> pixels) :
			imageData(pixels) {};

		/** \brief
		*
		* \return vector<unsigned char> Image data.
		*/
		std::vector<unsigned char> GetImageData() { return imageData; }

		~ImageResource() {};

	private:

		std::vector <unsigned char> imageData;

	};
}

#endif // IMAGERESOURCE_H