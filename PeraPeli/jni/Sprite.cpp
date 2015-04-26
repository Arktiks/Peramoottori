#include "Sprite.h"
#include "scene\Transformable.h"
#include "graphics\Rectangle.h"
#include "graphics\Drawable.h"
#include "graphics\Color.h"
Sprite::Sprite()
{
	gameEntity.AddComponent(NEW pm::Rectangle);
	gameEntity.AddComponent(NEW pm::Transformable);
	gameEntity.AddComponent(NEW pm::Drawable);
	gameEntity.AddComponent(NEW pm::Color);
}
Sprite::Sprite(pm::Texture* texture)
{
	gameEntity.AddComponent(NEW pm::Rectangle);
	gameEntity.AddComponent(NEW pm::Transformable);
	gameEntity.AddComponent(NEW pm::Drawable);
	gameEntity.AddComponent(NEW pm::Color);
	gameEntity.AddComponent(texture);
}


Sprite::~Sprite()
{
}

void Sprite::SetPosition(glm::vec2 position)
{
	gameEntity.GetComponent<pm::Transformable>()->SetPosition(position);
}
void Sprite::SetSize(glm::vec2 size)
{
	gameEntity.GetComponent<pm::Rectangle>()->SetSize(size);
}

void Sprite::SetOrigin(glm::vec2 origin)
{
	gameEntity.GetComponent<pm::Rectangle>()->SetOrigin(origin);
}

void Sprite::SetRotation(GLfloat rotation)
{
	gameEntity.GetComponent<pm::Transformable>()->SetRotation(rotation);
}
void Sprite::SetScale(glm::vec2 scale)
{
	gameEntity.GetComponent<pm::Transformable>()->SetScale(scale);
}

void Sprite::SetDepth(GLfloat depth)
{
	gameEntity.GetComponent<pm::Transformable>()->SetDepth(depth);
}
void Sprite::SetDrawState(bool state)
{
	gameEntity.GetComponent<pm::Drawable>()->SetDrawState(state);
}
void Sprite::SetColor(glm::vec4 color)
{
	gameEntity.GetComponent<pm::Color>()->SetColor(color);
}
void Sprite::SetTexture(pm::Texture* texture)
{
	gameEntity.AddComponent(texture);
}
glm::vec2 Sprite::GetPosition()
{
	return gameEntity.GetComponent<pm::Transformable>()->GetPosition();
}