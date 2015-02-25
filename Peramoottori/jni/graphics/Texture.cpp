#include "Texture.h"
using namespace pm;

// Tekstureen atlaskoordinaatit jotka tehdään resourcemanagerilla, lisäksi tieto mikä atlas on kyseessä, pointer?
// Tekstureen lisäksi käyttäjän asettamat tekstuurikoordinaatit, eli jos vaikka animoidaan niin mikä kohta teksuuria piirretään.

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