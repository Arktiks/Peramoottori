#include "Text.h"
#include "core\Log.h"
#include <GLES2/gl2.h>
#include <string>
namespace pm
{
	Text::Text(FontResource* font, TextResource* text, float x, float y, float w, float h)
	{
		GE = new GameEntity();
		FT_Library lib = font->GetLibrary();	//... initialize library ...
		FT_Face face = font->GetFace();			//... create face object ...

		FT_GlyphSlot  slot = face->glyph;
		int           pen_x, pen_y, n;


		FT_Error error = FT_Set_Char_Size(
			face,						/* handle to face object           */
			0,							/* char_width in 1/64th of points  */
			16 * 64,					/* char_height in 1/64th of points */
			300,						/* horizontal device resolution    */
			300);						/* vertical device resolution      */

		int num_chars = 1; //text->GetTextData().size();

		FT_UInt   glyph_index = 12;
		error = FT_Load_Glyph(face, FT_Get_Char_Index( face, 'B' ), FT_LOAD_DEFAULT);

		glm::vec2 position(x, y);
		glm::vec2 rightBottom(w, h);

		glGenTextures(1, &textId);
		glActiveTexture(textId);
		glBindTexture(GL_TEXTURE_2D, textId);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, slot->bitmap.width, slot->bitmap.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, slot->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		GE->AddComponent(NEW Rectangle(w, h));
		GE->AddComponent(NEW Transformable());
		
		GE->GetComponent<Transformable>()->SetPosition(position);
		GE->GetComponent<Transformable>()->SetRotation(0);
		GE->GetComponent<Transformable>()->SetScale(1, 1);
		

		GE->AddComponent(NEW Drawable());
		GE->GetComponent<Drawable>()->SetDrawState(true);

		GE->AddComponent(NEW Texture());
		GE->GetComponent<Texture>()->SetId(textId);
		//GE->GetComponent<Texture>()->SetTextureVertices(glm::vec2(0, 0), glm::vec2(1, 1));


		GE->AddComponent(NEW Color(glm::vec4(0.2f, 0.7f, 0.7f, 0.0f)));

		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);

	}
	Text::~Text()
	{

	}
}