#include "Rectangle.h"

pm::Rectangle::Rectangle(float width, float height) : Shape()
{
	this->width = width;
	this->height = height;

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			vertices.push_back(-origin.x + width * i); //1 xpos
			vertices.push_back(-origin.y + height * k); //2 ypos
			vertices.push_back(1.0f); //3 red
			vertices.push_back(0.0f); //4 green
			vertices.push_back(1.0f); //5 blue
			vertices.push_back(i); //6 txpos
			vertices.push_back(k); //7 typos
		}
	}

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(2);
}

pm::Rectangle::Rectangle(glm::vec2 size) : Shape()
{
	width = size.x;
	height = size.y;

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			vertices.push_back(-origin.x + width * i); //1 xpos
			vertices.push_back(-origin.y + height * k); //2 ypos
			vertices.push_back(1.0f); //3 red
			vertices.push_back(0.0f); //4 green
			vertices.push_back(1.0f); //5 blue
			vertices.push_back(i); //6 txpos
			vertices.push_back(k); //7 typos
		}
	}

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(1);
}

void pm::Rectangle::SetOrigin(glm::vec2 newOrigin)
{
	origin = newOrigin;

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			vertices.push_back(-origin.x + width * i); //1 xpos
			vertices.push_back(-origin.y + height * k); //2 ypos
			vertices.push_back(1.0f); //3 red
			vertices.push_back(0.0f); //4 green
			vertices.push_back(1.0f); //5 blue
			vertices.push_back(i); //6 txpos
			vertices.push_back(k); //7 typos
		}
	}
}

void pm::Rectangle::SetOrigin(float x, float y)
{
	SetOrigin(glm::vec2(x, y));
}


pm::Rectangle::~Rectangle()
{
}