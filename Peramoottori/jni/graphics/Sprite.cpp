#include "Sprite.h"


Sprite::Sprite()
{
	hasTexture = false;
}

Sprite::Sprite(Texture texture)
{
	this->texture = texture;
	hasTexture = true;
}

Sprite::~Sprite()
{
}

void Sprite::setSourceRectSize(glm::vec2 sourceRectSize)
{
	this->sourceRectSize = sourceRectSize;
}

void Sprite::setSourceRectPosition(glm::vec2 sourceRectPosition)
{
	this->sourceRectPosition = sourceRectPosition;
}