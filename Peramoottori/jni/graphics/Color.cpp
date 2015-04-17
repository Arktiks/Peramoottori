#include "Color.h"

pm::Color::Color() : Component()
{
	color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
};

pm::Color::Color(glm::vec4 color) : Component()
{
	(this->color) = color;
};

void pm::Color::SetColor(glm::vec4 newColor)
{
	color = newColor;
}

glm::vec4 pm::Color::GetColor()
{
	return color;
}