#include "Texture.h"
#include "resources\TextureFactory.h"
#include "string"

pm::Texture::Texture() : Component()
{
}

pm::Texture::Texture(std::string path) : Component()
{
	file = path;
	// !! CREATE A COPY CONSTRUCTOR OR SOMETHING; THIS IS PRONE TO ERRORS
	Texture* tempTexture = TextureFactory::CreateTexture(path);
	this->SetId(tempTexture->GetIdHandle());
	this->SetTextureSize(tempTexture->GetTextureSize());
	this->SetTrueSize(tempTexture->GetTrueSize());
	this->SetTranslucency(tempTexture->GetTranslucency());
	delete tempTexture;
}

void pm::Texture::SetTextureSize(glm::uvec2 textureSize)
{
	(this->textureSize.x) = textureSize.x;
	(this->textureSize.y) = textureSize.y;
}

void pm::Texture::SetTrueSize(glm::uvec2 textureSize)
{
	(this->trueSize.x) = textureSize.x;
	(this->trueSize.y) = textureSize.y;
}

void pm::Texture::SetId(GLuint* textureId)
{
	textureIndex = textureId;
}

GLuint pm::Texture::GetId()
{
	return *textureIndex;
}

glm::uvec2 pm::Texture::GetTextureSize()
{
	return textureSize;
}

glm::uvec2 pm::Texture::GetTrueSize()
{
	return trueSize;
}

uint pm::Texture::GetTextureGroup()
{
	return textureGroup;
}

void pm::Texture::SetTextureGroup(uint inTextureGroup)
{
	textureGroup = inTextureGroup;
}

void pm::Texture::SetTranslucency(pm::Texture::TRANSLUCENCY translucency)
{
	this->translucency = translucency; 
};

pm::Texture::TRANSLUCENCY pm::Texture::GetTranslucency()
{
	return translucency;
};