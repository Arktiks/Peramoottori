#ifndef SHAPE_H

#define SHAPE_H

#include <vector>
#include "glm\common.hpp"
static const double PI = 3.141;
class Shape
{
protected:

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	glm::vec2 position;
	glm::vec2 origin;
	glm::vec2 size;

	int rotation;

	float colorRed, colorGreen, colorBlue;

	int drawDepht;

	
};

#endif
