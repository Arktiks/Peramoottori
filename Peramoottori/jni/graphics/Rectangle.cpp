#include "Rectangle.h"
using namespace pm;

Rectangle::Rectangle(float tempPositionX, float tempPositionY, float tempWidht, float tempHeight)
{
	position = glm::vec2(tempPositionX, tempPositionY);
	size = glm::vec2(1, 1);
	widht = tempWidht;
	height = tempHeight;
	draw = true;

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			vertices.push_back(tempPositionX + tempWidht * i); //1 xpos
			vertices.push_back(tempPositionY + tempHeight * k); //2 ypos
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

Rectangle::Rectangle(glm::vec2 tempPosition, glm::vec2 tempWidthHeight)
{
	position = glm::vec2(tempPosition.x, tempPosition.y);
	size = glm::vec2(1, 1);
	widht = tempWidthHeight.x;
	height = tempWidthHeight.y;
	draw = true;

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			vertices.push_back(tempPosition.x + tempWidthHeight.x *i); //1 xpos
			vertices.push_back(tempPosition.y + tempWidthHeight.y *k); //2 ypos
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

void Rectangle::setPosition(glm::vec2 position)
{
	
	vertices[0] = position.x;
	vertices[1] = position.y;

	vertices[7] = position.x;
	vertices[8] = position.y + height;

	vertices[14] = position.x + widht;
	vertices[15] = position.y;

	vertices[21] = position.x + height;
	vertices[22] = position.y + widht;

	this->position = position;
};
void Rectangle::setSize(glm::vec2 size)
{
	//this->setSize(size);
}

Rectangle::~Rectangle()
{
}
