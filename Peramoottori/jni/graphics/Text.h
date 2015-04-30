#ifndef TEXT_H
#define TEXT_H
#include <resources\FontResource.h>
#include <resources\TextResource.h>
#include <scene\Texture.h>
#include <GLES2\gl2.h>
#include <scene\GameEntity.h>
#include <core\Memory.h>
#include <graphics\Rectangle.h>
#include <graphics\Color.h>
#include <graphics\Drawable.h>
#include <vector>

namespace pm
{
	class Text
	{
	public:

		Text(FontResource* font, TextResource* text, float x, float y, float w, float h);
		~Text();
		GameEntity* GetGameEntity(){ return GE; };

	private:

		int HEIGHT;
		int WIDTH;
		std::vector<float> vertexData;
		std::vector<uint> indexData;

		GLuint textId;

		GameEntity* GE;
	};
}
#endif
