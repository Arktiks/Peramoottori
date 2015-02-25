#include "Text.h"
using namespace pm;

Text::Text(const char* temptext, float tempx, float tempy, float tempwidht, float tempheight, Font tempfont)
{
	text = temptext;
	x = tempx;
	y = tempy;
	widht = tempwidht;
	height = tempheight;
	font = tempfont;
}

Text::~Text()
{
}

/*
void render_text(const char *text, float x, float y, float sx, float sy) {
const char *p;

for(p = text; *p; p++) {
if(FT_Load_Char(face, *p, FT_LOAD_RENDER))
continue;

glTexImage2D(
GL_TEXTURE_2D,
0,
GL_RED,
g->bitmap.width,
g->bitmap.rows,
0,
GL_RED,
GL_UNSIGNED_BYTE,
g->bitmap.buffer
);

float x2 = x + g->bitmap_left * sx;
float y2 = -y - g->bitmap_top * sy;
float w = g->bitmap.width * sx;
float h = g->bitmap.rows * sy;

GLfloat box[4][4] = {
{x2,     -y2    , 0, 0},
{x2 + w, -y2    , 1, 0},
{x2,     -y2 - h, 0, 1},
{x2 + w, -y2 - h, 1, 1},
};

glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

x += (g->advance.x >> 6) * sx;
y += (g->advance.y >> 6) * sy;
}
}
*/