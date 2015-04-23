#include "Transformable.h"

void pm::Transformable::SetPosition(glm::vec2 newPosition)
{
	position = newPosition;
}

void pm::Transformable::SetPosition(float newPositionX, float newPositionY)
{
	position = { newPositionX, newPositionY };
}

void pm::Transformable::SetScale(glm::vec2 newScale)
{
	scale = newScale;
}

void pm::Transformable::SetScale(float newScaleX, float newScaleY)
{
	scale = { newScaleX, newScaleY };
}

void pm::Transformable::SetRotation(float newRotation)
{
	rotation = newRotation;
}

void pm::Transformable::SetDepth(int newDepthValue)
{
	depthBuffer = newDepthValue;
}

glm::vec2 pm::Transformable::GetPosition()
{
	return position;
}

glm::vec2 pm::Transformable::GetScale()
{
	return scale;
}

float pm::Transformable::GetRotation()
{
	return rotation;
}

int pm::Transformable::GetDepth()
{
	return depthBuffer;
}