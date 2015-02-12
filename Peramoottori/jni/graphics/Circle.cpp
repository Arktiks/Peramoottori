#include "graphics/Circle.h"

Circle::Circle(float tempPositionX, float tempPositionY, float tempRadius, int tempSmoothness)
{
	radius = tempRadius;
	position = glm::vec2(tempPositionX, tempPositionY);
	size = glm::vec2(1, 1);


	for (int i = 0; i < tempSmoothness; i++)
	{
		vertices.push_back(tempPositionX + tempRadius * cos(PI / 2 + i * (PI * 2 / tempSmoothness)); //1 xpos
		vertices.push_back(tempPositionY + tempRadius * sin(PI / 2 + i * (PI * 2 / tempSmoothness)); //2 ypos
		vertices.push_back(0.0f); //3 red
		vertices.push_back(0.0f); //4 green
		vertices.push_back(0.0f); //5 blue
		vertices.push_back(cos(PI / 2 + i * (PI * 2 / tempSmoothness))); //6 txpos
		vertices.push_back(sin(PI / 2 + i * (PI * 2 / tempSmoothness))); //7 typos
	}

}
Circle::~Circle()
{

}