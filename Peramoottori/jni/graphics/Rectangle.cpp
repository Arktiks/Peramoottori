#include "Rectangle.h"

pm::Rectangle::Rectangle(float newWidth, float newHeight)
{
	widht = newWidth;
	height = newHeight;
	draw = true;

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			vertices.push_back(newWidth * i); //1 xpos
			vertices.push_back(newHeight * k); //2 ypos
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

pm::Rectangle::Rectangle(glm::vec2 size)
{
	widht = size.x;
	height = size.y;
	draw = true;

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			vertices.push_back(size.x *i); //1 xpos
			vertices.push_back(size.y *k); //2 ypos
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



pm::Rectangle::~Rectangle()
{
}
