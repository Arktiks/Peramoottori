#include "scene\Transformable.h"

pm::Transformable::Transformable()
{
	position = glm::vec2( 0.0f, 0.0f );
	origin = glm::vec2( 0.0f, 0.0f );
	scale = glm::vec2(0.0f, 0.0f );

	rotation = 0.0f;
};

pm::Transformable::Transformable(glm::vec2 position, glm::vec2 origin, glm::vec2 scale, float rotation)
{
	this->position = position;
	this->origin = origin;
	this->scale = scale;
	this->rotation = rotation;
}

void pm::Transformable::SetPosition(glm::vec2 newPosition)
{
	position = newPosition;
}

void pm::Transformable::SetPosition(float positionX, float positionY)
{
	position = { positionX, positionY };
}

void pm::Transformable::SetOrigin(glm::vec2 newOrigin)
{
	origin = newOrigin;
}

void pm::Transformable::SetOrigin(float originX, float originY)
{
	origin = { originX, originY };
}

void pm::Transformable::SetScale(glm::vec2 newScale)
{
	scale = newScale;
}

void pm::Transformable::SetScale(float scaleX, float scaleY)
{
	scale = { scaleX, scaleY };
}

void pm::Transformable::SetRotation(float newRotation)
{
	rotation = newRotation;
}
