#include "Texture.h"
#include "resources\TextureFactory.h"
#include "string"

pm::Texture::Texture() : Component()
{
	//this = TextureFactory::CreateTexture();

}

pm::Texture::Texture(std::string path) : Component()
{
	Texture* tex = TextureFactory::CreateTexture(path);
	this->SetId(tex->GetId());
	this->SetTextureSize(tex->GetTextureSize());
}

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