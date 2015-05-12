#ifndef TEXT_H
#define TEXT_H
#include <resources\FontResource.h>
#include <resources\TextResource.h>
#include <scene\GameEntity.h>
#include <vector>

namespace pm
{
	class Text
	{
	public:

		/**
		* Text Constructor need FontResource, TextResource, texts begining point (x,y), 
		* and the height and width of the desired text.
		*/
		Text(FontResource* font, TextResource* text, float x, float y, float w, float h);
		
		~Text();

		GameEntity* GetGameEntity() { return GE; } ///< Returns generated GameEntity that text has created.

		std::vector<GameEntity*> GetTextVector() { return textVector; } ///< Returns generated GameEntity that text has created.
	
	private:

		/**
		* Makes a single GameEntity out of a single char
		* that is stored in textVector.
		*/
		void Textasd(FontResource* font, char c, float x, float y, float w, float h);

		int HEIGHT;
		int WIDTH;

		GLuint textId;
		FT_GlyphSlot  slot;

		GameEntity* GE;

		std::vector<GameEntity*> textVector;///< GameEntity Vector that houses GameEntitys that make up the text.
	};
}

#endif