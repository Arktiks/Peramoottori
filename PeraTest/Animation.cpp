#include "Animation.h"
#include <scene\GameEntity.h>
#include <core\Memory.h>
Animation::Animation()
{
	frameSizeX = 0;
	frameSizeY = 0;
	animationFrame = 0;
	frameAmountX = 1;
	frameAmountY = 1;
	frameAmount = 1;
	timeBetweenFrame = 0.1;
	updateTime = 0;
	frameDir = 1;
	scaleDir = 0.1;
}
Animation::Animation(float updateRate)
{
	frameSizeX = 0;
	frameSizeY = 0;
	animationFrame = 0;
	frameAmountX = 1;
	frameAmountY = 1;
	frameAmount = 1;
	timeBetweenFrame = updateRate;
	updateTime = 0;
	frameDir = 1;
	scaleDir = 0.1;
}

Animation::~Animation()
{
}
void Animation::SetParent(pm::GameEntity* entity)
{
	parent = entity;
	if (parent->GetComponent<UpdateRate>() == nullptr)
	parent->AddComponent(NEW UpdateRate(timeBetweenFrame));
}

void Animation::SetValues(int frameSizeX, int frameSizeY, int animationFrame, 
	int frameAmount, int frameAmountX, int frameAmountY)
{
	this->frameSizeX = frameSizeX;
	this->frameSizeY = frameSizeY;
	this->animationFrame = animationFrame;
	this->frameAmountX = frameAmountX;
	this->frameAmountY = frameAmountY;
	this->frameAmount = frameAmount;

}

void Animation::GenerateCoords()
{
	int xCoord=0, yCoord=0;
	glm::vec4 animCoords;
	for (int i = 0; i < frameAmount; i++)
	{
		if (frameAmountX <= xCoord)
		{
			xCoord = 0;
			yCoord++;
		}
		animCoords = glm::vec4(xCoord*frameSizeX, yCoord*frameSizeY,
			(xCoord + 1)*frameSizeX, (yCoord + 1)*frameSizeY);
		xCoord++;
		animationCoordinates.push_back(animCoords);
	}
}