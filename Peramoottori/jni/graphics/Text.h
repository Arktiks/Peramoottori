#ifndef TEXT_H
#define TEXT_H
#include <resources\FontResource.h>
#include <resources\TextResource.h>

class Text
{
public:

	Text(pm::FontResource* font, pm::TextResource* text);
	~Text();

	void show_image();
	void draw_bitmap(FT_Bitmap* bitmap, FT_Int x, FT_Int y);

private:

	int HEIGHT;
	int WIDTH;

	unsigned char* image[];

};
#endif
