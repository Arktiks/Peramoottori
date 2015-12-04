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

using namespace pm;

Text::Text(FontResource* font, TextResource* text, float x, float y, float w, float h)
{
	Initialise(font, text->GetTextData(), x, y, w, h);
}

Text::Text(FontResource* font, std::string text, float x, float y, float w, float h)
{
	Initialise(font, text, x, y, w, h);
}

Text::Text(Resource* font, Resource* text, float x, float y, float w, float h)
{
	auto t = (TextResource*)text;
	Initialise((FontResource*)font, t->GetTextData(), x, y, w, h);
}

Text::Text(Resource* font, std::string text, float x, float y, float w, float h)
{
	Initialise((FontResource*)font, text, x, y, w, h);
}

void Text::ReText(TextResource* text)
{
	savedText = text->GetTextData();
	ReText(savedFont, text, X, Y, WIDTH, HEIGHT);
}

void Text::ReText(FontResource* font, TextResource* text, float x, float y, float w, float h)
{
	savedFont = font;
	savedText = text->GetTextData();;
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
	int size = savedText.size();
	for (int i = 0; i < size; i++)
	{
		x0 += w * 1.125;
		if (savedText[i + 1] == '\n')
		{
			x0 = x;
			y0 += h * 1.125;
			i++;
		}
		else if (savedText[i] == ' ')
		{
			x0 -= w * 0.5;
		}
		else
			Character(savedFont, savedText[i], x0, y0, w, h);
	}
}

std::vector<GameEntity*> Text::GetTextVector()
{
	if (textVector.size() != 0)
		return textVector;
	else
		return std::vector<GameEntity*>();
}

Text::~Text()
{
}

void Text::Initialise(FontResource* font, std::string text, float x, float y, float width, float height)
{
	float x0 = x;
	float y0 = y;

	X = x;
	Y = y;

	HEIGHT = height;
	WIDTH = width;

	savedFont = font;
	savedText = text;

	name = font->GetName();

	for (int i = 0; i < text.size(); i++)
	{
		int y = 0;
		int z = 0;
		x0 += width * 1.125;
		if (text[i + 1] == '\n')
		{
			x0 = x;
			y0 += height * 1.125;
			i++;
		}
		else if (text[i] == ' ')
		{
			x0 -= width * 0.5;
		}
		else
		{
			Character(font, text[i], x0, y0, width, height);
		}
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

	glm::vec2 vec = textTexture->GetTrueSize();
	glm::vec2 veci = textTexture->GetTextureSize();

	GameEntity* GE = NEW GameEntity();

	glm::vec2 position(x, y);

	GE->AddComponent(NEW Rectangle(w,h));
	GE->GetComponent<Rectangle>()->SetOrigin(w/2,h/2);

	GE->AddComponent(NEW Transformable());
	GE->GetComponent<Transformable>()->SetScale(uw / (450 / (w / 20)), uh / (450 / (h / 20)));
	GE->GetComponent<Transformable>()->SetPosition(position);
	GE->GetComponent<Transformable>()->SetRotation(0);
	GE->GetComponent<Transformable>()->SetDepth(9);

	GE->AddComponent(NEW Drawable());
	GE->GetComponent<Drawable>()->SetDrawState(true);

	GE->AddComponent(textTexture);

	GE->AddComponent(NEW Color(glm::vec4(1,0,0,1)));

	glActiveTexture(0u);
	glBindTexture(GL_TEXTURE_2D, 0u);

	textVector.push_back(GE);
}