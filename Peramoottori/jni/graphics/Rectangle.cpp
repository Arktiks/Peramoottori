#include "Rectangle.h"

pm::Rectangle::Rectangle(float width, float height) : Shape()
{
	this->width = width;
	this->height = height;

	SetVertices();
	SetIndices();
}

pm::Rectangle::Rectangle(glm::vec2 size) : Shape()
{
	width = size.x;
	height = size.y;

	SetVertices();
	SetIndices();
}

void pm::Rectangle::SetOrigin(glm::vec2 newOrigin)
{
	origin = newOrigin;

	SetVertices();
}

void pm::Rectangle::SetOrigin(float newOriginX, float newOriginY)
{
	SetOrigin(glm::vec2(newOriginX, newOriginY));
}

pm::Rectangle::~Rectangle()
{
}

void pm::Rectangle::SetVertices()
{
	vertices.clear();

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			vertices.push_back(-origin.x + width * i); //1 xpos
			vertices.push_back(-origin.y + height * k); //2 ypos
		}
	}
}

void pm::Rectangle::SetIndices()
{
	indices.clear();

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(1);
}