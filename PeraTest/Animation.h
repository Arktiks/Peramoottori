#ifndef ANIMATION_H
#define ANIMATION_H
#include <glm\common.hpp>
#include <scene\Component.h>
#include "UpdateRate.h"
#include <vector>
class Animation :public pm::Component
{
public:
	Animation();
	Animation(float updateRate);
	~Animation();
	void SetParent(pm::GameEntity* entity);
	void SetValues(int frameSizeX, int frameSizeY, int animationFrame,
		int frameAmount, int frameAmountX, int frameAmountY);

	int frameSizeX;
	int frameSizeY;

	int animationFrame;
	int frameDir;
	float scaleDir;

	int frameAmountX;
	int frameAmountY;
	int frameAmount;

	float timeBetweenFrame;
	float updateTime;
	void GenerateCoords();
	std::vector<glm::vec4> animationCoordinates;
	
};

#endif