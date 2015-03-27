#include "Sprite.h"
using namespace pm;

Sprite::Sprite() : Rectangle(0, 0, 0, 0)
{
	hasTexture = false;
	draw = true;
}

Sprite::Sprite(Texture texture) : Rectangle(glm::vec2(0,0), texture.getTextureSize())
{
	this->texture = texture;
	hasTexture = true;
	draw = true;
	//setSourceRectPosition(texture.getTexturePosition());
	//setSourceRectSize(texture.getTextureSize());
}

Sprite::Sprite(Texture texture, float x, float y, float widht, float heigth) : Rectangle(x, y, widht, heigth)
{
	this->texture = texture;
	hasTexture = true;
	draw = true;
}

Sprite::~Sprite()
{

}

void Sprite::setSourceRectSize(glm::vec2 tempsourceRectSize)
{
	this->sourceRect.x = tempsourceRectSize.x;
	this->sourceRect.y = tempsourceRectSize.y;

	vertices[6 + 7 * 1] = (tempsourceRectSize.y / texture.getTextureSize().y + 100);
	vertices[5 + 7 * 2] = (tempsourceRectSize.x / texture.getTextureSize().x);

	vertices[6 + 7 * 3] = (tempsourceRectSize.y / texture.getTextureSize().y);		// Tekstuurikoordinaattien piirrossa tässä kohdassa on virhe(itä).
	vertices[5 + 7 * 3] = (tempsourceRectSize.x / texture.getTextureSize().x);
}

void Sprite::setSourceRectPosition(glm::vec2 tempsourceRectPosition)
{
	this->sourceRect.x = tempsourceRectPosition.x;
	this->sourceRect.y = tempsourceRectPosition.y;

	vertices[5] = (tempsourceRectPosition.x / texture.getTextureSize().x + 100);
	vertices[6] = (tempsourceRectPosition.y / texture.getTextureSize().y);
}

void Sprite::setSourceRect(glm::vec4 tempsourceRect)
{
	this->sourceRect = tempsourceRect;

	vertices[5] = (tempsourceRect[0] / texture.getTextureSize()[0] + 100);
	vertices[6] = (tempsourceRect[1] / texture.getTextureSize()[1]);
	vertices[6 + 7 * 1] = (tempsourceRect[3] / texture.getTextureSize().y);
	vertices[5 + 7 * 2] = (tempsourceRect[2] / texture.getTextureSize().x);
	vertices[5 + 7 * 3] = (tempsourceRect[2] / texture.getTextureSize().x);
	vertices[6 + 7 * 3] = (tempsourceRect[3] / texture.getTextureSize().y);
}

glm::vec2 Sprite::getSourceRectSize()
{
	return glm::vec2(sourceRect[2], sourceRect[3]);
}

glm::vec2 Sprite::getSourceRectPosition()
{
	return glm::vec2(sourceRect[0], sourceRect[1]);
}

glm::vec4 Sprite::getSourceRect()
{
	return sourceRect;
}
