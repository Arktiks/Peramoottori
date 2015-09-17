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

		/**
		* Function can be used to change text resource
		* font , text, position, and / or size
		*/
		void ReText(FontResource* font, TextResource* text, float x, float y, float w, float h);

		~Text();

		std::vector<GameEntity*> GetTextVector()
		{
			if (textVector.size() != 0)return textVector;
			else
			{
				return std::vector<GameEntity*>();
			}

		} ///< Returns generated GameEntity that text has created.


		/**
		* Reinitializes Text after the app is in focus again.
		* For inner engine use only!
		*/
		void ReintializeFont(std::string s);

		/**
		* Reinitializes Text after the app is in focus again.
		* For inner engine use only!
		*/
		void ReintializeText(std::string s);

		/**
		* 
		* For inner engine use only!
		*/
		TextResource* GetTextResource(){ return savedText; };

		/**
		* 
		* For inner engine use only!
		*/
		FontResource* GetFontResource(){ return savedFont; };

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
		TextResource* savedText;

		GLuint textId;
		FT_GlyphSlot  slot;


		std::vector<GameEntity*> textVector;///< GameEntity Vector that houses GameEntitys that make up the text.
	};
}

#endif