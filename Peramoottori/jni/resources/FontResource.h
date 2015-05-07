#ifndef FONTRESOURCE_H
#define FONTRESOURCE_H

#include <resources\Resource.h>
#include <vector>

#include <include\ft2build.h>
#include FT_FREETYPE_H

namespace pm
{
	class FontResource : public Resource
	{
	public:

		//FontResource();

		FontResource(std::vector<FT_Byte> ttfData) :
			ttfData(ttfData) {};

		std::vector<FT_Byte> GetTTFData() { return ttfData; }

		~FontResource() {};
		
	private:
	
		std::vector<FT_Byte> ttfData;

	};
}

#endif //!FONTRESOURCE_H