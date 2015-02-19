#ifndef FONT_H

#define FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include "System\PMdebug.h"
#include "System\PMassert.h"
#include "string"

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

#endif