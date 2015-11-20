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
				Character(font, text->GetTextData()[i], x0, y0, w, h);
			}

		}

	}
	void Text::ReText(TextResource* text)
	{
		savedText = text;

		ReText(savedFont, text, X, Y, WIDTH, HEIGHT);

	}
	void Text::ReText(FontResource* font, TextResource* text, float x, float y, float w, float h)
	{
		savedFont = font;
		savedText = text;

		ReText(x, y, w, h);
	}

	void Text::ReText(float x, float y, float w, float h)
	{
		for (int i = 0; i < textVector.size(); i++)
			delete textVector.at(i);
		textVector.clear();
		float x0 = x;

		X = x;
		Y = y;
		HEIGHT = h;
		WIDTH = w;

		name = savedFont->GetName();
		float y0 = y;
		int size = savedText->GetTextData().size();
		for (int i = 0; i < size; i++)
		{
			x0 += w * 1.125;
			if (savedText->GetTextData()[i + 1] == '\n')
			{
				x0 = x;
				y0 += h * 1.125;
				i++;
			}
			else if (savedText->GetTextData()[i] == ' ')
			{
				x0 -= w * 0.5;
			}
			else
				Character(savedFont, savedText->GetTextData()[i], x0, y0, w, h);
		}
	}

	void Text::ReintializeFont(std::string s)
	{
		savedFont = (FontResource*)ResourceManager::GetInstance()->LoadAsset(s);
	}

	void Text::ReintializeText(std::string s)
	{
		ReText((TextResource*)ResourceManager::GetInstance()->LoadAsset(s));
	}

	void Text::Character(FontResource* font, char c, float x, float y, float w, float h)
	{
		float uw = font->GetCharacterWidth(c); 
		float uh = font->GetCharacterHeight(c);

		Texture *textTexture = font->GetTexture(c);
		textTexture->SetTrueSize(glm::vec2(uw, uh));
		textTexture->SetTextureSize(glm::vec2(uw, uh));
		//

		GameEntity* GE = NEW GameEntity();

		glm::vec2 position(x, y);

		GE->AddComponent(NEW Rectangle(w,h));
		GE->GetComponent<Rectangle>()->SetOrigin(w/2,h/2);
		GE->AddComponent(NEW Transformable());

		GE->GetComponent<Transformable>()->SetScale(uw / (450 / (w / 20)), uh / (450 / (h / 20)));

		GE->GetComponent<Transformable>()->SetPosition(position);
		GE->GetComponent<Transformable>()->SetRotation(0);

		GE->AddComponent(NEW Drawable());
		GE->GetComponent<Drawable>()->SetDrawState(true);

		GE->AddComponent(textTexture);

		//std::vector<float> clr = font->GetColor();

		GE->AddComponent(NEW Color(glm::vec4(1,0,0,1)));

		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		textVector.push_back(GE);
	}


	Text::~Text()
	{
	}
}