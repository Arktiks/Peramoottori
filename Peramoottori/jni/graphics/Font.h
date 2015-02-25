#ifndef FONT_H
#define FONT_H

#include <string>
#include <freetype\ft2build.h>
#include FT_FREETYPE_H

namespace pm
{
	class Font
	{
	public:

		Font();
		Font(const char* filePath);
		~Font();

	private:

		FT_Library library;
		FT_Face face;
		FT_GlyphSlot glyphSlot;

	};
}

#endif