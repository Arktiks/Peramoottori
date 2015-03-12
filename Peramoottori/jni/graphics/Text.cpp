#include "Text.h"
using namespace pm;

Text::Text(const char* temptext, float tempx, float tempy, Font tempFont)
{
	text = temptext;
	x = tempx;
	y = tempy;
	font = tempFont;

	//glBindTexture(GL_TEXTURE_2D, font.fontTexture);
	
	//while (*temptext)
	//{
	//	if (*temptext >= 32 && *temptext < 128)
	//	{
	//		
	//	}
	//	temptext++;
	//}



}

//Text::~Text()
//{

//}

