#ifndef TEXT_H
#define TEXT_H

#include "stb_easy_font.h"
#include "GLES2\gl2.h"
#include "Shader.h"

namespace pm
{
	class Text
	{

	public:

		Text(float tempx, float tempy, char *temptext, float tempred, float tempgreen, float tempblue);
		~Text();

		void Render();

	private:

		const char* text;

		float red, green, blue;

		static char buffer[99999]; // ~500 chars

		Shader textVShader;
		Shader textIShader;

		GLuint textVertexBuffer;
		GLuint textIndexBuffer;
		

	};
}

#endif