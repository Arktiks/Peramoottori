#include "Font.h"
#include <system\PMassert.h>
#include <system\PMdebug.h>
#include <string>
#include <stdio.h>
#include "resources\ResourceReader.h"
using namespace pm;

Font::Font()
{}
Font::Font(const char* filePath)
{
	unsigned char temp_bitmap[512 * 512];
	ResourceReader* rr;
	const unsigned char* ttf_buffer = (const unsigned char*)(rr->ReadText("ARLRDBD.TTF").c_str());
	stbtt_BakeFontBitmap(ttf_buffer, 0, 32.0, temp_bitmap, 512, 512, 32, 96, cdata);
	//glGenTextures(1, &fontTexture);
	//glBindTexture(GL_TEXTURE_2D, fontTexture);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 5121, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glBindTexture(GL_TEXTURE_2D, 0u);
}

Font::~Font()
{

}