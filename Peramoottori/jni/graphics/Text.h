#ifndef TEXT_H
#define TEXT_H
#include <resources\FontResource.h>
#include <resources\TextResource.h>
#include <scene\GameEntity.h>
#include <vector>
#include <string>

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

		std::vector<GameEntity*> GetTextVector() { return textVector; } ///< Returns generated GameEntity that text has created.
		
		void ReintializeText();

		std::string name;

	private:

		/**
		* Makes a single GameEntity out of a single char
		* that is stored in textVector.
		*/
		void Character(FontResource* font, char c, float x, float y, float w, float h);

		

		float HEIGHT;
		float WIDTH;
		float X;
		float Y;

		FontResource* savedFont;
		TextResource* savedtext;

		GLuint textId;
		FT_GlyphSlot  slot;


		std::vector<GameEntity*> textVector;///< GameEntity Vector that houses GameEntitys that make up the text.
	};
}

#endif