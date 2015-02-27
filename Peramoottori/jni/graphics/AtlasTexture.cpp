#include "AtlasTexture.h"


AtlasTexture::AtlasTexture(GLuint atlasIndex, glm::vec2 texturePosition, glm::vec2 textureSize)
{
	this->atlasIndex = atlasIndex;
	this->texturePosition = texturePosition;
	this->textureSize = textureSize;
}


AtlasTexture::~AtlasTexture()
{
}

glm::vec2 AtlasTexture::getTexturePosition()
{

}
glm::vec2 AtlasTexture::getTextureSize()
{

}
GLuint AtlasTexture::getAtlasIndex()
{

}