#include "Text.h"

using namespace pm;

Text::Text(float tempx, float tempy, char *temptext, float tempred, float tempgreen, float tempblue)
{
	text = temptext;

	int num_quads;

	num_quads = stb_easy_font_print(tempx, tempy, temptext, NULL, buffer, sizeof(buffer));

	textVShader.LoadShader("TextVertexShader.txt", GL_VERTEX_SHADER);
	textVShader.LoadShader("TextIndexShader.txt", GL_VERTEX_SHADER);


	glGenBuffers(1, &textVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textVertexBuffer);
	glBufferData(textVertexBuffer, 0, buffer, GL_TEXTURE_2D);


	glGenBuffers(1, &textIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textIndexBuffer);
	glBufferData(textIndexBuffer, 0, buffer, GL_TEXTURE_2D);

	red = tempred;
	green = tempgreen;
	blue = tempblue;

}

void Text::Render()
{

	glEnableVertexAttribArray(POS_LOCATION);


	glVertexAttribPointer(POS_LOCATION, 2, GL_FLOAT, GL_FALSE, 16, buffer); // Position

	glEnableVertexAttribArray(TEX_LOCATION);



	glVertexAttribPointer(TEX_LOCATION, 2, GL_FLOAT, GL_FALSE, 16, buffer + 8); // Texture coords

	glVertexAttrib3f(COL_LOCATION, red, green, blue);

}

//glGenBuffers(1, &bufferPtr);
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferPtr);
//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indiceSize, indices, GL_STATIC_DRAW);
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
//return bufferPtr;


void print_string(float x, float y, char *text, float r, float g, float b)
{
	static char buffer[99999]; // ~500 chars
	int num_quads;

	num_quads = stb_easy_font_print(x, y, text, NULL, buffer, sizeof(buffer));

	/*glColor3f(r, g, b);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 16, buffer);
	glDrawArrays(GL_QUADS, 0, num_quads * 4);
	glDisableClientState(GL_VERTEX_ARRAY);*/
}