#ifndef TEXT_H
#define TEXT_H

#include <resources\FontResource.h>
#include <resources\TextResource.h>
#include <scene\GameEntity.h>
#include <vector>
#include <string>

namespace pm
{
	/** \brief Create renderable %text.
	*
	* \ingroup Graphics
	*/

	class Text
	{

		friend class TextureFactory;

	public:

		/**
		* \param[in] font Pointer to FontResource.
		* \param[in] text Pointer to TextResource.
		* \param[in] x location on x-axis. 
		* \param[in] y location on y-axis.
		* \param[in] w width of Text.
		* \param[in] h height of Text.
		*/
		Text(FontResource* font, TextResource* text, float x, float y, float w, float h);

		/** \brief Can be used to set values of Text object. */
		void ReText(TextResource* text);
		/** \brief Can be used to set values of Text object. */
		void ReText(FontResource* font, TextResource* text, float x, float y, float w, float h);
		/** \brief Can be used to set values of Text object. */
		void ReText(float x, float y, float w, float h);

		~Text();

		/** \brief When pm::Text is initialized it creates std::vector of GameEntity
		* objects to work as %text.
		*
		* \return std::vector<GameEntity*> of GameEntity objects created.
		* \return empty std::vector<GameEntity*> if there is no text.
		*/
		std::vector<GameEntity*> GetTextVector()
		{
			if (textVector.size() != 0)
				return textVector;
			else
				return std::vector<GameEntity*>();
		}

		std::string name;

		/** \internal Made following four functions private .
		* If they are indeed only for engine use we can just make TextureFactory friend class.
		*/	
		FontResource* GetFontResource(){ return savedFont; };


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


	private:


		/**
		* 
		* For inner engine use only!
		*/
		TextResource* GetTextResource(){ return savedText; };

		/**
		* 
		* For inner engine use only!
		*/
	



	private:

		/** Makes a single GameEntity out of a single char that is stored in textVector. */
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