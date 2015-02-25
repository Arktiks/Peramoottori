#include "Texture.h"
using namespace pm;

// Tekstureen atlaskoordinaatit jotka tehd��n resourcemanagerilla, lis�ksi tieto mik� atlas on kyseess�, pointer?
// Tekstureen lis�ksi k�ytt�j�n asettamat tekstuurikoordinaatit, eli jos vaikka animoidaan niin mik� kohta teksuuria piirret��n.

Texture::Texture(int atlas, glm::vec2 texturePosition, glm::vec2 textureSize)
{
	atlasIndex = atlas;
	this->texturePosition = texturePosition;
	this->textureSize = textureSize;
}

Texture::Texture()
{
}

Texture::~Texture()
{
}

glm::vec2 Texture::getTexturePosition()
{
	return texturePosition;
}

glm::vec2 Texture::getTextureSize()
{
	return textureSize;
}

int Texture::getAtlasID()
{
	return atlasIndex;
}