#include "Text.h"
#include <GLES2\gl2.h>

#include <core\Log.h>
#include <core\Memory.h>
#include <scene\Texture.h>
#include <graphics\Rectangle.h>
#include <graphics\Color.h>
#include <graphics\Drawable.h>
#include <resources\TextureFactory.h>
#include <resources\ResourceManager.h>

namespace pm
{
	Text::Text(FontResource* font, TextResource* text, float x, float y, float w, float h)
	{
		float x0 = x;

		X = x;
		Y = y;
		HEIGHT = h;
		WIDTH = w;

		savedFont = font;
		savedText = text;

		name = font->GetName();
		float y0 = y;
		int size = text->GetTextData().size();
		for (int i = 0; i < size; i++)
		{
			int y = 0;
			int z = 0;
			x0 += w * 1.125;
			if (text->GetTextData()[i + 1] == '\n')
			{
				x0 = x;
				y0 += h * 1.125;
				i++;
			}
			else if (text->GetTextData()[i] == ' ')
			{
				x0 -= w * 0.5;
			}
			else
			{
				if      (text->GetTextData()[i] == 'a'){ y0 += h * .2; y = 1;}
				else if (text->GetTextData()[i] == 'c'){ y0 += h * .2; y = 1;}
				else if (text->GetTextData()[i] == 'e'){ y0 += h * .2; y = 1;}
				else if (text->GetTextData()[i] == 'm'){ y0 += h * .2; y = 1; z = -2; }
				else if (text->GetTextData()[i] == 'n'){ y0 += h * .2; y = 1;}
				else if (text->GetTextData()[i] == 'o'){ y0 += h * .2; y = 1;}
				else if (text->GetTextData()[i] == 'p'){ y0 += h * .2; y = 1;}
				else if (text->GetTextData()[i] == 'g'){ y0 += h * .2; y = 1;}
				else if (text->GetTextData()[i] == 'q'){ y0 += h * .2; y = 1;}
				else if (text->GetTextData()[i] == 'i'){ z = 1; }
				else if (text->GetTextData()[i] == 'j'){ z = 1; }
				else if (text->GetTextData()[i] == 'r'){ y0 += h * .2; y = 1;}
				else if (text->GetTextData()[i] == 's'){ y0 += h * .2; y = 1;}
				else if (text->GetTextData()[i] == 'u'){ y0 += h * .2; y = 1;}
				else if (text->GetTextData()[i] == 'ä'){ y0 += h * .1; y = 4;}
				else if (text->GetTextData()[i] == 'ö'){ y0 += h * .1; y = 4;}
				else if (text->GetTextData()[i] == 't'){ z = 1; }
				else if (text->GetTextData()[i] == 'l'){ z = 1; }
				else if (text->GetTextData()[i] == 'v'){ y0 += h * .2; y = 1;}
				else if (text->GetTextData()[i] == 'w'){ y0 += h * .2; y = 1; z = -2; }
				else if (text->GetTextData()[i] == 'x'){ y0 += h * .2; y = 1;}
				else if (text->GetTextData()[i] == 'y'){ y0 += h * .2; y = 1;}
				else if (text->GetTextData()[i] == 'z'){ y0 += h * .2; y = 1;}
				else if (text->GetTextData()[i] == 'I'){ z = 1; }
				else if (text->GetTextData()[i] == 'J'){ y = 1; }
				else if (text->GetTextData()[i] == 'G'){ z = -2; }
				else if (text->GetTextData()[i] == 'A'){ z = -2; }
				else if (text->GetTextData()[i] == 'Å'){ z = -2; }
				else if (text->GetTextData()[i] == 'C'){ z = -2; }

				else if (text->GetTextData()[i] == 'W'){ z = -1; y0 += h * .2; y = 1; }
				else if (text->GetTextData()[i] == 'O'){ z = -2; y0 += h * .2; y = 1; }
				else if (text->GetTextData()[i] == 'M'){ z = -2; y0 += h * .2; y = 1; }
				else if (text->GetTextData()[i] == 'Q'){ z = -2; y0 += h * .2; y = 1; }

				else if (text->GetTextData()[i] == 'K'){ y0 += h * .2; y = 1; }
				else if (text->GetTextData()[i] == 'L'){ y0 += h * .2; y = 1; }
				else if (text->GetTextData()[i] == 'N'){ y0 += h * .2; y = 1; }
				else if (text->GetTextData()[i] == 'P'){ y0 += h * .2; y = 1; }
				else if (text->GetTextData()[i] == 'R'){ y0 += h * .2; y = 1; }
				else if (text->GetTextData()[i] == 'S'){ y0 += h * .2; y = 1; }
				else if (text->GetTextData()[i] == 'T'){ y0 += h * .2; y = 1; }
				else if (text->GetTextData()[i] == 'U'){ y0 += h * .2; y = 1; }
				else if (text->GetTextData()[i] == 'V'){ y0 += h * .2; y = 1; }
				else if (text->GetTextData()[i] == 'X'){ y0 += h * .2; y = 1; }
				else if (text->GetTextData()[i] == 'Y'){ y0 += h * .2; y = 1; }
				else if (text->GetTextData()[i] == 'Z'){ y0 += h * .2; y = 1; }

				else if (text->GetTextData()[i] == '.'){ y0 += h * .55; y = 2; }
				else if (text->GetTextData()[i] == ','){ y0 += h * .55; y = 2; }
				else if (text->GetTextData()[i] == '+'){ y0 += h * .2 ; y = 1; }
				else if (text->GetTextData()[i] == '-'){ y0 += h * .35; y = 3; }
				else if (text->GetTextData()[i] == '*'){ y0 += h * .2 ; y = 1; }
				else if (text->GetTextData()[i] == '='){ y0 += h * .2 ; y = 1; }



				Character(font, text->GetTextData()[i], x0, y0, w, h);
				if (y == 1)y0 -= h * .2;
				if (y == 2)y0 -= h * .55;
				if (y == 3)y0 -= h * .35;
				if (y == 4)y0 -= h * .1;
				if (z == 1)x0 -= w * .5;
				if (z == -1)x0 += w * .5;
				if (z == -2)x0 += w * .25;
			}

		}

		pm::TextureFactory::SaveText(this);
	}

	void Text::ReText(FontResource* font, TextResource* text, float x, float y, float w, float h)
	{
		for (int i = 0; i < textVector.size(); i++)
			textVector.at(i)->~GameEntity();
		textVector.clear();
		float x0 = x;

		X = x;
		Y = y;
		HEIGHT = h;
		WIDTH = w;

		savedFont = font;
		savedText = text;

		name = font->GetName();
		float y0 = y;
		int size = text->GetTextData().size();
		for (int i = 0; i < size; i++)
		{
			x0 += w * 1.125;
			if (text->GetTextData()[i + 1] == '\n')
			{
				x0 = x;
				y0 += h * 1.125;
				i++;
			}
			else if (text->GetTextData()[i] == ' ')
			{
				x0 -= w * 0.5;
			}
			else
				Character(font, text->GetTextData()[i], x0, y0, w, h);
		}
	}

	void Text::ReintializeFont(std::string s)
	{
		savedFont = (FontResource*)ResourceManager::GetInstance()->LoadAsset(s);
	}
	void Text::ReintializeText(std::string s)
	{
		//textVector.clear();
		std::vector<GameEntity*> tempEntityVector;
		savedText = new pm::TextResource(s);
		for (int i = 0; i < savedText->GetTextData().size(); i++)
		{
			GameEntity* GE = NEW GameEntity();

			FT_Library  library;

			FT_Error error = FT_Init_FreeType(&library);
			if (error)
				DEBUG_INFO(("Failed to initialize freetype library!"));

			FT_Face face;

			std::vector<FT_Byte> ttf = savedFont->GetTTFData();

			error = FT_New_Memory_Face(library,
				&ttf[0],
				ttf.size(),
				0,
				&face);
			if (error == FT_Err_Unknown_File_Format)
			{
				DEBUG_INFO(("The font file could be opened and read, but it appears that its font format is unsupported"));
			}
			else if (error)
			{
				DEBUG_INFO(("Font file could not be opened or read, or it is broken"));
			}

			FT_GlyphSlot  slot = face->glyph;

			error = FT_Set_Char_Size(
				face,						/* handle to face object           */
				0,							/* char_width in 1/64th of points  */
				32 * 64,					/* char_height in 1/64th of points */
				1280,						/* horizontal device resolution    */
				720);						/* vertical device resolution      */

			glm::vec2 position(X, Y);
			glm::vec2 rightBottom(WIDTH, HEIGHT);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			glGenTextures(1, &textId);
			glActiveTexture(textId);
			glBindTexture(GL_TEXTURE_2D, textId);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			float ux = slot->bitmap_left;
			float uy = slot->bitmap_top;

			float uw = slot->bitmap.width;
			float uh = slot->bitmap.rows;

			FT_UInt glyph_index;

			glyph_index = FT_Get_Char_Index(face, savedText->GetTextData().at(i));

			FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER);

			FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, slot->bitmap.width, slot->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, slot->bitmap.buffer);

			WIDTH = 10;
			HEIGHT = 10;

			GE->AddComponent(NEW Rectangle(slot->bitmap.width, slot->bitmap.rows));
			GE->AddComponent(NEW Transformable());

			//float scaleY = slot->bitmap.width / slot->bitmap.rows;
			//if (scaleY < 1)
			//	GE->GetComponent<Transformable>()->SetScale(1, 1);
			//else
			GE->GetComponent<Transformable>()->SetScale(slot->bitmap.width, slot->bitmap.rows);

			GE->GetComponent<Transformable>()->SetPosition(position);
			GE->GetComponent<Transformable>()->SetRotation(0);

			GE->AddComponent(NEW Drawable());
			GE->GetComponent<Drawable>()->SetDrawState(true);

			GE->AddComponent(NEW Texture());
			GE->GetComponent<Texture>()->SetId(textId);
			GE->GetComponent<Texture>()->SetTextureSize(glm::vec2(slot->bitmap.width, slot->bitmap.rows));

			GE->AddComponent(NEW Color(glm::vec4(0.0f, 0.8f, 0.0f, 0.0f)));

			glActiveTexture(0);
			glBindTexture(GL_TEXTURE_2D, 0);

			tempEntityVector.push_back(GE);
		}
		textVector = tempEntityVector;

	}

	void Text::Character(FontResource* font, char c, float x, float y, float w, float h)
	{
		GameEntity* GE = NEW GameEntity();

		FT_Library  library;

		FT_Error error = FT_Init_FreeType(&library);
		if (error)
			DEBUG_INFO(("Failed to initialize freetype library!"));

		FT_Face face;

		std::vector<FT_Byte> ttf = font->GetTTFData();

		error = FT_New_Memory_Face(library,
			&ttf[0],
			ttf.size(),
			0,
			&face);
		if (error == FT_Err_Unknown_File_Format)
		{
			DEBUG_INFO(("The font file could be opened and read, but it appears that its font format is unsupported"));
		}
		else if (error)
		{
			DEBUG_INFO(("Font file could not be opened or read, or it is broken"));
		}

		FT_GlyphSlot  slot = face->glyph;

		error = FT_Set_Char_Size(
			face,						/* handle to face object           */
			0,							/* char_width in 1/64th of points  */
			32 * 64,					/* char_height in 1/64th of points */
			1280,						/* horizontal device resolution    */
			720);						/* vertical device resolution      */

		glm::vec2 position(x, y);
		glm::vec2 rightBottom(w, h);                             

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, &textId);
		glActiveTexture(textId);
		glBindTexture(GL_TEXTURE_2D, textId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		float ux = slot->bitmap_left;
		float uy = slot->bitmap_top;
				  
		float uw = slot->bitmap.width;
		float uh = slot->bitmap.rows;

		FT_UInt glyph_index;

		glyph_index = FT_Get_Char_Index(face, c);

		FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER);

		FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, slot->bitmap.width, slot->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, slot->bitmap.buffer);
		
		GE->AddComponent(NEW Rectangle(slot->bitmap.width / (16 / (w / 20)), slot->bitmap.rows / (16 / (h / 20))));
		GE->AddComponent(NEW Transformable());
		
		//float scaleY = slot->bitmap.width / slot->bitmap.rows;
		//if (scaleY < 1)
		//	GE->GetComponent<Transformable>()->SetScale(slot->bitmap.width, slot->bitmap.rows);
		//else
		GE->GetComponent<Transformable>()->SetScale(1,1);

		GE->GetComponent<Transformable>()->SetPosition(position);
		GE->GetComponent<Transformable>()->SetRotation(0);

		GE->AddComponent(NEW Drawable());
		GE->GetComponent<Drawable>()->SetDrawState(true);

		GE->AddComponent(NEW Texture());
		GE->GetComponent<Texture>()->SetId(textId);
		GE->GetComponent<Texture>()->SetTextureSize(glm::vec2(slot->bitmap.width, slot->bitmap.rows));

		std::vector<float> clr = font->GetColor();

		GE->AddComponent(NEW Color(glm::vec4(clr[0], clr[1], clr[2], clr[3])));

		//GE->AddComponent(NEW Color(glm::vec4(0.0f, 0.8f, 0.8f, 0.0f)));

		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		textVector.push_back(GE);
	}


	Text::~Text()
	{
	}
}