#include "graphics\Font.h"


Font::Font(const char* filePath)
{
	if (FT_Init_FreeType(&library))
	{
		PMdebug::MsgInfo("%s", "Could not initialize Freetype");
	}

	if (FT_New_Face(library, filePath, 0, &face))
	{
		PMdebug::MsgInfo("%s","Could not open font");
	}
	glyphSlot = face->glyph;
}

Font::~Font()
{
}