#include "Circle.h"

pm::Circle::Circle(float radius, int iterations) : Shape()
{
	this->radius = radius;

	vertices.push_back(origin.x); //1 xpos
	vertices.push_back(origin.y); //2 ypos
	vertices.push_back(0.0f); //3 red
	vertices.push_back(0.0f); //4 green
	vertices.push_back(0.0f); //5 blue
	vertices.push_back(0.0f); //6 txpos
	vertices.push_back(0.0f); //7 typos
	
	for (int i = 0; i < iterations; i++)
	{
		vertices.push_back(origin.x + radius * cos(PI / 2 + i * (PI * 2 / iterations))); //1 xpos
		vertices.push_back(origin.y + radius * sin(PI / 2 + i * (PI * 2 / iterations))); //2 ypos
		vertices.push_back(0.0f); //3 red
		vertices.push_back(0.0f); //4 green
		vertices.push_back(0.0f); //5 blue
		vertices.push_back(cos(PI / 2 + i * (PI * 2 / iterations))); //6 txpos
		vertices.push_back(sin(PI / 2 + i * (PI * 2 / iterations))); //7 typos
	}

}

pm::Circle::~Circle()
{
}