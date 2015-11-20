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

		/**
		* \param[in] font Pointer to FontResource.
		* \param[in] std::string text.
		* \param[in] x location on x-axis.
		* \param[in] y location on y-axis.
		* \param[in] w width of Text.
		* \param[in] h height of Text.
		*/
		Text(FontResource* font, std::string text, float x, float y, float w, float h);

		Text(Resource* font, Resource* text, float x, float y, float w, float h);

		Text(Resource* font, std::string text, float x, float y, float w, float h);

		/** \brief Can be used to set values of Text object. */
		void ReText(TextResource* text);
		/** \brief Can be used to set values of Text object. */
		void ReText(FontResource* font, TextResource* text, float x, float y, float w, float h);
		/** \brief Can be used to set values of Text object. */
		void ReText(float x, float y, float w, float h);

		/** \brief When pm::Text is initialized it creates std::vector of GameEntity
		* objects to work as %text.
		*
		* \return std::vector<GameEntity*> of GameEntity objects created.
		* \return empty std::vector<GameEntity*> if there is no text.
		*/
		std::vector<GameEntity*> GetTextVector();

		std::string name; ///< Name of font.

		~Text();

	private:

		void Initialise(FontResource* font, std::string text,
			float x, float y, float width, float height);

		/** \internal Following are for inner engine use only! */

		FontResource* GetFontResource() { return savedFont; }

		/** \brief Reinitializes Font after the app is in focus again.
		*
		* Notes.
		*/
		void ReintializeFont(std::string s);

		/** \brief Reinitializes Text after the app is in focus again.
		* 
		* Notes.
		*/
		void ReintializeText(std::string s);

		/** \brief Derp.
		* 
		* Notes.
		*/
		std::string GetTextResource() { return savedText; }

	private:

		/** Makes GameEntity out of single char that is stored in textVector. */
		void Character(FontResource* font, char c, float x, float y, float w, float h);

		float HEIGHT;
		float WIDTH;
		float X;
		float Y;
		
		FontResource* savedFont;
		std::string savedText;

		GLuint textId;
		FT_GlyphSlot  slot;

		std::vector<GameEntity*> textVector; ///< GameEntity Vector that houses GameEntities that make up the text.
	};
}

#endif