#include "SpriteObject.h"
#include <scene\Transformable.h>
#include <graphics\Rectangle.h>
#include <graphics\Drawable.h>
#include <graphics\Color.h>

SpriteObject::SpriteObject()
{
	AddComponent(NEW pm::Rectangle);
	AddComponent(NEW pm::Transformable);
	AddComponent(NEW pm::Drawable);
	AddComponent(NEW pm::Color);
}
SpriteObject::SpriteObject(pm::Texture* texture)
{
	AddComponent(NEW pm::Rectangle);
	AddComponent(NEW pm::Transformable);
	AddComponent(NEW pm::Drawable);
	AddComponent(NEW pm::Color);
	AddComponent(texture);
}

SpriteObject::~SpriteObject()
{
}

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
void SpriteObject::SetScale(float scaleX, float scaleY)
{
	SetScale(glm::vec2(scaleX, scaleY));
}

void SpriteObject::SetDepth(GLfloat depth)
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
void SpriteObject::SetTexture(pm::Texture* texture)
{
	AddComponent(texture);
}
glm::vec2 SpriteObject::GetPosition()
{
	return GetComponent<pm::Transformable>()->GetPosition();
}

glm::vec2 SpriteObject::GetSize()
{
	return GetComponent<pm::Rectangle>()->GetSize();
}