#ifndef TEXT_H

#define TEXT_H

#include "graphics\Font.h"


class Text
{

public:

	Text(const char* text, float x, float y, float widht, float height, Font font);
	~Text();

private:
	
	const char* text;
	float x, y, widht, height;

	Font font;
};

#endif