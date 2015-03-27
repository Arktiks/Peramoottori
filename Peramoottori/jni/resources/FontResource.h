#ifndef FONTRESOURCE_H
#define FONTRESOURCE_H

#include <resources\Resource.h>

namespace pm
{
	class FontResource : public Resource
	{
	public:
		FontResource();
		FontResource(const unsigned char data);

		const unsigned char getFontData();

		~FontResource();
	private:
		unsigned char fontData;
	};
}
#endif //!FONTRESOURCE_H
