#include <scene\TextureCoordinates.h>
#include <scene\GameEntity.h>
#include <scene\Texture.h>

pm::TextureCoordinates::TextureCoordinates()
{
	textureCoordinates.resize(4);
	SetTextureCoordinates(-1, -1, 1, 1);		
}

pm::TextureCoordinates::TextureCoordinates(float left, float top, float right, float bottom)
{
	textureCoordinates.resize(4);
	SetTextureCoordinates(left, top, right, bottom);
}

pm::TextureCoordinates::TextureCoordinates(glm::vec2 leftTop, glm::vec2 rightBottom)
{
	textureCoordinates.resize(4);
	SetTextureCoordinates(leftTop[0], leftTop[1], rightBottom[0], rightBottom[1]);
}

pm::TextureCoordinates::TextureCoordinates(glm::vec4 coordinates)
{
	textureCoordinates.resize(4);
	SetTextureCoordinates(coordinates[0], coordinates[1], coordinates[2], coordinates[3]);
}

void pm::TextureCoordinates::SetTextureCoordinates(float left, float top, float right, float bottom)
{
	textureCoordinates[0] = left;
	textureCoordinates[1] = bottom;
	textureCoordinates[2] = right;
	textureCoordinates[3] = top;
}

void pm::TextureCoordinates::SetParent(GameEntity* parent)
{
	this->parent = parent;
	Texture* tempTexturePointer = parent->GetComponent<Texture>();
	if (tempTexturePointer != nullptr && textureCoordinates[0] == -1)
		SetTextureCoordinates(0, 0, tempTexturePointer->GetTrueSize().x, tempTexturePointer->GetTrueSize().y);
}

void pm::TextureCoordinates::SetTextureDimensions(float left, float top, float width, float height) //Should this be more clear?
{
	textureCoordinates[0] = left;
	textureCoordinates[1] = top+height;
	textureCoordinates[2] = left+width;
	textureCoordinates[3] = top;
}

void  pm::TextureCoordinates::SetTextureDimensions(glm::vec2 leftTop, glm::vec2 widthHeight)
{
	textureCoordinates[0] = leftTop.x;
	textureCoordinates[1] = leftTop.y + widthHeight.y;
	textureCoordinates[2] = leftTop.x + widthHeight.x;
	textureCoordinates[3] = leftTop.y;
}

void  pm::TextureCoordinates::SetTextureDimensions(glm::vec4 leftTopWidthHeight)
{
	textureCoordinates[0] = leftTopWidthHeight.x;
	textureCoordinates[1] = leftTopWidthHeight.y + leftTopWidthHeight.w;
	textureCoordinates[2] = leftTopWidthHeight.x + leftTopWidthHeight.z;
	textureCoordinates[3] = leftTopWidthHeight.y;
}

void pm::TextureCoordinates::SetTextureCoordinates(glm::vec2 leftTop, glm::vec2 rightBottom)
{
	SetTextureCoordinates(leftTop[0], leftTop[1], rightBottom[0], rightBottom[1]);
}

void pm::TextureCoordinates::SetTextureCoordinates(glm::vec4 coordinates)
{
	SetTextureCoordinates(coordinates[0], coordinates[1], coordinates[2], coordinates[3]);
}
