#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

namespace pm
{
	/// Contains picture as unsigned char.
	/// Currently does not support picture dimensions.

	class Image
	{
	public:
		/// Default constructor.
		Image() /*: width(0), height(0)*/ {};

		/// Constructor that takes in picture data.
		Image(std::vector<unsigned char> pixels) : /*width(0), height(0),*/ pixels(pixels) {};

		/// Destructor.
		~Image() {};

		//unsigned int width; ///< Picture width, not supported.
		//unsigned int height; ///< Picture height, not supported.
		std::vector<unsigned char> pixels; ///< Picture data.
	};
}

#endif