#ifndef ANIMATION_H
#define ANIMATION_H
#include <glm\common.hpp>
#include <scene\Component.h>
#include <vector>
class Animation :public pm::Component
{
public:
	Animation();
	~Animation();
	void SetValues(int frameSizeX, int frameSizeY, int animationFrame, 
		int frameAmount, int frameAmountX, int frameAmountY, float timeBetweenFrame);

	int frameSizeX;
	int frameSizeY;

	int animationFrame;

	int frameAmountX;
	int frameAmountY;
	int frameAmount;

	float timeBetweenFrame;

	void GenerateCoords();
	std::vector<glm::vec4> animationCoordinates;
	
};

#endif