#ifndef COLOR_H
#define COLOR_H

#include <scene\Component.h>
#include <glm\vec4.hpp>

namespace pm
{
	class Color : public Component
	{
	public:
		Color();
		Color(glm::vec4 color);

		void SetColor(glm::vec4 newColor);
		glm::vec4 GetColor();

	private:
		glm::vec4 color;
	};
}

#endif //COLOR_H