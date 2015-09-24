#include "MultipleTexture.h"


MultipleTexture::MultipleTexture()
{
}


MultipleTexture::~MultipleTexture()
{
	//for (std::vector<pm::Texture*>::iterator it = textures.begin(); it != textures.end(); it++)
	//{
	//	delete *it;
	//}

}

void MultipleTexture::AddTexture(pm::Texture* texture)
{
	textures.push_back(texture);
}

void MultipleTexture::SetTextureVector(std::vector<pm::Texture*> textures)
{
	this->textures = textures;
}