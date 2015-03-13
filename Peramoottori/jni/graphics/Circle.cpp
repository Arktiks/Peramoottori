#include "Circle.h"

pm::Circle::Circle(float tempPositionX, float tempPositionY, float tempRadius, int tempSmoothness)
{
	radius = tempRadius;
	transformable.SetPosition(tempPositionX, tempPositionY);
	transformable.SetScale(1, 1);
	draw = true;

	vertices.push_back(tempPositionX); //1 xpos
	vertices.push_back(tempPositionY); //2 ypos
	vertices.push_back(0.0f); //3 red
	vertices.push_back(0.0f); //4 green
	vertices.push_back(0.0f); //5 blue
	vertices.push_back(0.0f); //6 txpos
	vertices.push_back(0.0f); //7 typos


	for (int i = 0; i < tempSmoothness; i++)
	{
		vertices.push_back(tempPositionX + tempRadius * cos(PI / 2 + i * (PI * 2 / tempSmoothness))); //1 xpos
		vertices.push_back(tempPositionY + tempRadius * sin(PI / 2 + i * (PI * 2 / tempSmoothness))); //2 ypos
		vertices.push_back(0.0f); //3 red
		vertices.push_back(0.0f); //4 green
		vertices.push_back(0.0f); //5 blue
		vertices.push_back(cos(PI / 2 + i * (PI * 2 / tempSmoothness))); //6 txpos
		vertices.push_back(sin(PI / 2 + i * (PI * 2 / tempSmoothness))); //7 typos
	}

}

pm::Circle::~Circle()
{
}