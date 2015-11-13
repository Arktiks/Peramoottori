#include "SpriteObject.h"
#include <core\Memory.h>
#include <scene\Transformable.h>
#include <scene\TextureCoordinates.h>
#include <graphics\Rectangle.h>
#include <graphics\Drawable.h>
#include <graphics\Color.h>


SpriteObject::SpriteObject()
{
	AddComponent(NEW pm::Transformable());
	AddComponent(NEW pm::TextureCoordinates());
	AddComponent(NEW pm::Rectangle());
	AddComponent(NEW pm::Drawable());
	AddComponent(NEW pm::Color());
}

SpriteObject::SpriteObject(pm::Texture* texture)
{
	AddComponent(texture);
	AddComponent(NEW pm::Rectangle(texture->GetTextureSize()));
	AddComponent(NEW pm::TextureCoordinates(0.0f, 0.0f, texture->GetTrueSize().x, texture->GetTrueSize().y));
	AddComponent(NEW pm::Transformable());
	AddComponent(NEW pm::Drawable());
	AddComponent(NEW pm::Color());
}

SpriteObject::SpriteObject(std::string filename)
{
	Texture* tempTexture = NEW Texture(filename);
	AddComponent(tempTexture);
	AddComponent(NEW pm::Rectangle(tempTexture->GetTextureSize()));
	AddComponent(NEW pm::TextureCoordinates(0.0f, 0.0f, tempTexture->GetTrueSize().x, tempTexture->GetTrueSize().y));
	AddComponent(NEW pm::Transformable());
	AddComponent(NEW pm::Drawable());
	AddComponent(NEW pm::Color());
}

SpriteObject::~SpriteObject()
{
}

void SpriteObject::Update(float deltaTime){}

void SpriteObject::SetPosition(glm::vec2 position)
{
	GetComponent<pm::Transformable>()->SetPosition(position);
}

void SpriteObject::SetPosition(float positionX, float positionY)
{
	SetPosition(glm::vec2(positionX, positionY));
}

void SpriteObject::SetSize(glm::vec2 size)
{
	GetComponent<pm::Rectangle>()->SetSize(size);
}

void SpriteObject::SetSize(float width, float height)
{
	SetSize(glm::vec2(width, height));
}

void SpriteObject::SetOrigin(glm::vec2 origin)
{
	GetComponent<pm::Rectangle>()->SetOrigin(origin);
}

void SpriteObject::SetOrigin(float originX, float originY)
{
	SetOrigin(glm::vec2(originX, originY));
}

void SpriteObject::SetRotation(GLfloat rotation)
{
	GetComponent<pm::Transformable>()->SetRotation(rotation);
}

void SpriteObject::SetScale(glm::vec2 scale)
{
	GetComponent<pm::Transformable>()->SetScale(scale);
}

void SpriteObject::SetScale(float scaleWidth, float scaleHeight)
{
	SetScale(glm::vec2(scaleX, scaleY));
}

void SpriteObject::SetDepth(float depth)
{
	GetComponent<pm::Transformable>()->SetDepth(depth);
}

void SpriteObject::SetDrawState(bool state)
{
	GetComponent<pm::Drawable>()->SetDrawState(state);
}

void SpriteObject::SetColor(glm::vec4 color)
{
	GetComponent<pm::Color>()->SetColor(color);
}

glm::vec4 SpriteObject::GetColor()
{
	return GetComponent<pm::Color>()->GetColor();
}

void SpriteObject::SetTexture(pm::Texture* texture)
{
	AddComponent(texture);
	SetTextureCoordinates(glm::vec4(0.0f, 0.0f, texture->GetTextureSize().x, texture->GetTextureSize().y));
}

void SpriteObject::SetTexture(std::string filename)
{
	Texture* tempTexture = new Texture(filename);
	AddComponent(texture);
	SetTextureCoordinates(glm::vec4(0.0f, 0.0f, tempTexture->GetTextureSize().x, tempTexture->GetTextureSize().y));
}
//  Get current SpriteObject position
glm::vec2 SpriteObject::GetPosition()
{
	return GetComponent<pm::Transformable>()->GetPosition();
}

glm::vec2 SpriteObject::GetSize()
{
	return GetComponent<pm::Rectangle>()->GetSize();
}

GLfloat SpriteObject::GetRotation()
{
	return GetComponent<pm::Transformable>()->GetRotation();
}

glm::vec2 SpriteObject::GetOrigin()
{
	return GetComponent<pm::Rectangle>()->GetOrigin();
}

void SpriteObject::SetTextureCoordinates(glm::vec4 textureCoordinates)
{
	GetComponent<TextureCoordinates>()->SetTextureCoordinates(textureCoordinates);
}

void SpriteObject::SetTextureCoordinates(glm::vec2 leftTop, glm::vec2 rightBottom)
{
	GetComponent<TextureCoordinates>()->SetTextureCoordinates(leftTop, rightBottom);
}

void SpriteObject::SetTextureCoordinates(float left, float top, float right, float bottom)
{
	GetComponent<TextureCoordinates>()->SetTextureCoordinates(left, top, right, bottom);
}

void SpriteObject::SetTextureDimensions(glm::vec4 textureDimensions)
{
	GetComponent<TextureCoordinates>()->SetTextureDimensions(textureCoordinates);
}

void SpriteObject::SetTextureDimensions(glm::vec2 leftTop, glm::vec2 widthHeight)
{
	GetComponent<TextureCoordinates>()->SetTextureDimensions(leftTop, widthHeight);
}

void SpriteObject::SetTextureDimensions(float left, float top, float width, float height)
{
	GetComponent<TextureCoordinates>()->SetTextureDimensions(left, top, width, height);
}