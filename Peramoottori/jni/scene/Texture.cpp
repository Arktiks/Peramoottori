#include "Texture.h"

void pm::Texture::SetTextureSize(glm::uvec2 textureSize)
{
	(this->textureSize.x) = textureSize.x;
	(this->textureSize.y) = textureSize.y;
}

void pm::Texture::SetId(GLuint textureId)
{
	textureIndex = textureId;
}

GLuint pm::Texture::GetId()
{
	return textureIndex;
}

glm::uvec2 pm::Texture::GetTextureSize()
{
	return textureSize;
}