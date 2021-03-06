#ifndef IMAGERESOURCE_H
#define IMAGERESOURCE_H

#include <resources\Resource.h>
#include <vector>

namespace pm
{
	/** \internal Functions should be described with more detail. */
	/** \brief
	*
	* Long description.
	*
	* \ingroup Resources
	*/

	class ImageResource : public Resource
	{
		friend class ResourceManager;

	public:

		/** \brief Disabled default constructor
		*/
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


		std::vector <unsigned char> imageData;

	};
}

#endif // IMAGERESOURCE_H