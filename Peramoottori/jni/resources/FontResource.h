#ifndef FONTRESOURCE_H
#define FONTRESOURCE_H

#include <resources\Resource.h>
#include <include\ft2build.h>
#include FT_FREETYPE_H

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
	
		
		FT_Library library;
		unsigned char fontData;
	};
}
#endif //!FONTRESOURCE_H
