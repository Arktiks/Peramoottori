#include "Triangle.h"
#include "Triangle.h"

pm::Triangle::Triangle(float tempPositionX, float tempPositionY, float tempRadius)
{
	radius = tempRadius;
	transformable.SetPosition(tempPositionX, tempPositionY);
	transformable.SetScale(1, 1);
	draw = true;

	for (int i = 0; i < 3; i++)
	{
		vertices.push_back(tempPositionX + tempRadius * cos(PI / 2 + i * (PI * 2 / 3))); //1 xpos
		vertices.push_back(tempPositionY + tempRadius * sin(PI / 2 + i * (PI * 2 / 3))); //2 ypos
		vertices.push_back(0.0f); //3 red
		vertices.push_back(0.0f); //4 green
		vertices.push_back(0.0f); //5 blue
		vertices.push_back(cos(PI / 2 + i * (PI * 2 / 3))); //6 txpos
		vertices.push_back(sin(PI / 2 + i * (PI * 2 / 3))); //7 typos
	}

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
}

pm::Triangle::~Triangle()
{
}