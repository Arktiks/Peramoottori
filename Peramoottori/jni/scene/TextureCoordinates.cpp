#include <scene\TextureCoordinates.h>

pm::TextureCoordinates::TextureCoordinates()
{
	textureCoordinates.resize(4);
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
	textureCoordinates[1] = top;
	textureCoordinates[2] = right;
	textureCoordinates[3] = bottom;
}

void pm::TextureCoordinates::SetTextureCoordinates(glm::vec2 leftTop, glm::vec2 rightBottom)
{
	SetTextureCoordinates(leftTop[0], leftTop[1], rightBottom[0], rightBottom[1]);
}

void pm::TextureCoordinates::SetTextureCoordinates(glm::vec4 coordinates)
{
	SetTextureCoordinates(coordinates[0], coordinates[1], coordinates[2], coordinates[3]);
}