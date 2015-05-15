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

		/// constructor
		FontResource(std::vector<FT_Byte> ttfData) :
			ttfData(ttfData) 
		{
			//SetColor(1, 0, 1, 1);
		};

		///returns FT_Byte vector, that is the data of the font
		std::vector<FT_Byte> GetTTFData() { return ttfData; }

		/// sets the color of the font
		//void SetColor(float red, float green, float blue, float alpha)
		//{
		//	color.at(0) = red;
		//	color.at(1) = green;
		//	color.at(2) = blue;
		//	color.at(3) = alpha;
		//};

		/// return float vector, thats first four values are the rgba values of the font
		std::vector<float> GetColor() { return color; };
		~FontResource() {};
		
	private:
	
		std::vector<FT_Byte> ttfData;
		std::vector<float> color;

	};
}

#endif //!FONTRESOURCE_H