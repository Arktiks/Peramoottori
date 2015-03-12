#ifndef FONT_H
#define FONT_H

#include <string>
#include <GLES2\gl2.h>
#include "stb_truetype.h"
#define STB_TRUETYPE_IMPLEMENTATION



namespace pm
{
	class Font
	{
	public:

		Font();
		Font(const char* filePath);
		~Font();

		stbtt_bakedchar cdata[96];
		GLuint fontTexture;
	};
}

#endif