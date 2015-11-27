#include "Color.h"

pm::Color::Color() : Component()
{
	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

pm::Color::Color(glm::vec4 color) : Component()
{
	(this->color) = color;
}
pm::Color::Color(float red, float green, float blue, float alpha)
{
	color = glm::vec4(red, green, blue, alpha);
}

void pm::Color::SetColor(glm::vec4 newColor)
{
	color = newColor;
}
void pm::Color::SetColor(float red, float green, float blue, float alpha)
{
	color = glm::vec4(red, green, blue, alpha);
}

glm::vec4 pm::Color::GetColor()
{
	return color;
}