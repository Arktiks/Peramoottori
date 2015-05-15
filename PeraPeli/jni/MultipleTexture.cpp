#include "MultipleTexture.h"


MultipleTexture::MultipleTexture()
{
}


MultipleTexture::~MultipleTexture()
{
}

void MultipleTexture::AddTexture(pm::Texture* texture)
{
	textures.push_back(texture);
}

void MultipleTexture::SetTextureVector(std::vector<pm::Texture*> textures)
{
	this->textures = textures;
}