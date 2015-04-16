#include "Sprite.h"


Sprite::Sprite(std::vector<GLfloat> vertexData, std::vector<GLushort> indexData,
	glm::mat4 transformMatrix, GLuint textureIndex)
{
	this->vertexData = vertexData;
	this->indexData = indexData;
	this->transformMatrix = transformMatrix;
	this->textureIndex = textureIndex;
}

void Sprite::SetData(std::vector<GLfloat> vertexData, std::vector<GLushort> indexData,
	glm::mat4 transformMatrix, GLuint textureIndex)
{
	this->vertexData = vertexData;
	this->indexData = indexData;
	this->transformMatrix = transformMatrix;
	this->textureIndex = textureIndex;
}

Sprite::~Sprite()
{
}
