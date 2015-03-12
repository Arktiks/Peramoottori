#ifndef TEXT_H
#define TEXT_H

#include "Font.h"

namespace pm
{
	class Text
	{

	public:

		Text(const char* text, float x, float y, Font font);
		~Text();

	private:

		const char* text;
		float x, y;

		Font font;

	};
}

#endif