#include "Texture.h"


pm::Texture::Texture() : Component()
{	
}

void pm::Texture::SetId(GLuint ui)
{
	textureIndex = ui;
}

void pm::Texture::SetTextureSize(glm::uvec2 v2)
{

	textureSize.x = v2.x;
	textureSize.y = v2.y;

}

GLuint pm::Texture::getId()
{
	return textureIndex;
}
glm::uvec2 pm::Texture::getTextureSize()
{
	return textureSize;
}