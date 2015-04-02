#include "scene\Transformable.h"

pm::Transformable::Transformable() : 
Transformable(	glm::vec2(0.0f, 0.0f), 
				glm::vec2(0.0f, 0.0f), 
				0.0f)
{};

pm::Transformable::Transformable(glm::vec2 position, glm::vec2 scale, float rotation) : Component()
{
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
	depthBuffer = 0;
}

pm::Transformable::~Transformable()
{

}

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

void pm::Transformable::SetDepth(float newDepthValue)
{
	depthBuffer = newDepthValue;
}