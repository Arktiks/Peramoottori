#include "Text.h"


Text::Text(pm::FontResource* font, pm::TextResource* text)
{
	FT_GlyphSlot  slot = font->GetFace()->glyph;  /* a small shortcut */
	int           pen_x, pen_y, n;

	FT_Library lib = font->GetLibrary();//... initialize library ...
	FT_Face face = font->GetFace();//... create face object ...

	int error = FT_Set_Char_Size(
		face,						/* handle to face object           */
		0,							/* char_width in 1/64th of points  */
		16 * 64,					/* char_height in 1/64th of points */
		300,						/* horizontal device resolution    */
		300);						/* vertical device resolution      */

	
	
	int num_chars = text->getTextData().size();

	pen_x = 300;
	pen_y = 200;

	for (n = 0; n < num_chars; n++)
	{
		FT_UInt  glyph_index;


		/* retrieve glyph index from character code */
		glyph_index = FT_Get_Char_Index(face, text->getTextData()[n]);

		/* load glyph image into the slot (erase previous one) */
		error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
		if (error)
			continue;  /* ignore errors */

		/* convert to an anti-aliased bitmap */
		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
		if (error)
			continue;

		/* now, draw to our target surface */
		draw_bitmap(&slot->bitmap,
			pen_x + slot->bitmap_left,
			pen_y - slot->bitmap_top);

		/* increment pen position */
		pen_x += slot->advance.x >> 6;
		pen_y += slot->advance.y >> 6; /* not useful for now */
	}

}

void Text::draw_bitmap(FT_Bitmap* bitmap, FT_Int x, FT_Int y)
{
	FT_Int  i, j, p, q;
	FT_Int  x_max = x + bitmap->width;
	FT_Int  y_max = y + bitmap->rows;


	for (i = x, p = 0; i < x_max; i++, p++)
	{
		for (j = y, q = 0; j < y_max; j++, q++)
		{
			if (i < 0 || j < 0 ||
				i >= WIDTH || j >= HEIGHT)
				continue;

			image[j][i] |= bitmap->buffer[q * bitmap->width + p];
		}
	}
}

Text::~Text()
{
}

void Text::show_image(void)
{
	int  i, j;
	HEIGHT = 600;
	WIDTH = 400;

	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
			putchar(image[i][j] == 0 ? ' '
			: image[i][j] < 128 ? '+'
			: '*');
		putchar('\n');
	}
}