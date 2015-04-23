#ifndef TEXT_H
#define TEXT_H
#include <resources\FontResource.h>
#include <resources\TextResource.h>
#include <scene\Texture.h>
#include <GLES2\gl2.h>
#include <scene\GameEntity.h>
#include <core\Memory.h>
#include <graphics/Rectangle.h>
#include <vector>
#include <graphics\Drawable.h>


namespace pm
{
	class Text : public GameEntity
	{
	public:

		Text(FontResource* font, TextResource* text, float x, float y, float w, float h);
		~Text();

	private:

		int HEIGHT;
		int WIDTH;
		std::vector<float> vertexData;
		std::vector<uint> indexData;

		GLuint textId;
	};
}
#endif
