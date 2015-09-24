#include "SpriteObject.h"
#include <scene\Transformable.h>
#include <PhysicComponent.h>
#include <graphics\Rectangle.h>
#include <graphics\Drawable.h>
#include <graphics\Color.h>
#include <scene\TextureCoordinates.h>

// Create default SpriteObject without texture
SpriteObject::SpriteObject()
{
	done = false;
	AddComponent(NEW pm::Rectangle());
	AddComponent(NEW pm::Transformable());
	AddComponent(NEW pm::Drawable());
	AddComponent(NEW pm::Color());
	AddComponent(NEW pm::TextureCoordinates());
}
// Crete SpriteObject with texture
SpriteObject::SpriteObject(pm::Texture* texture)
{
	done = false;
	AddComponent(NEW pm::Rectangle(texture->GetTextureSize()));
	AddComponent(NEW pm::Transformable());
	AddComponent(NEW pm::Drawable());
	AddComponent(NEW pm::Color());
	AddComponent(NEW pm::TextureCoordinates(0.0f, 0.0f, texture->GetTextureSize().x, texture->GetTextureSize().y));
	AddComponent(texture);

}

SpriteObject::~SpriteObject()
{
}

void SpriteObject::Update(float deltaTime){}

// Add physics component (Not in use)
void SpriteObject::AddPhysics()
{
	AddComponent(NEW PhysicComponent);
	GetComponent<PhysicComponent>()->SetPosition(GetComponent<pm::Transformable>()->GetPosition());
}

// Set velocity (requires physics-component)
void SpriteObject::SetVelocity(glm::vec2 velocity)
{
	if (GetComponent<PhysicComponent>() == nullptr)
	{
		return;
	}
	else
		GetComponent<PhysicComponent>()->SetVelocity(velocity);
}
// Get current velocity (requires physics-component)
glm::vec2 SpriteObject::GetVelocity()
{
	if (GetComponent<PhysicComponent>() == nullptr)
	{
		return glm::vec2(0, 0);
	}
	else
		return GetComponent<PhysicComponent>()->GetVelocity();
}
// Set new position using vec2
void SpriteObject::SetPosition(glm::vec2 position)
{
	// TODO: CHECK IF THIS DOES ANYTHING ATM
	if (GetComponent<PhysicComponent>() == nullptr)
	{}
	else
		GetComponent<PhysicComponent>()->SetPosition(position);
	GetComponent<pm::Transformable>()->SetPosition(position);
}
// Set new position using two values.
void SpriteObject::SetPosition(float positionX, float positionY)
{
	SetPosition(glm::vec2(positionX, positionY));
}
// Set new size for rectangle using vec2
void SpriteObject::SetSize(glm::vec2 size)
{
	GetComponent<pm::Rectangle>()->SetSize(size);
}
// Set new size for rectangle using two values
void SpriteObject::SetSize(float width, float height)
{
	SetSize(glm::vec2(width, height));
}
// Set new origin for rectangle using vec2
void SpriteObject::SetOrigin(glm::vec2 origin)
{
	GetComponent<pm::Rectangle>()->SetOrigin(origin);
}
// Set new origin for rectangle using two values
void SpriteObject::SetOrigin(float originX, float originY)
{
	SetOrigin(glm::vec2(originX, originY));
}
// Set new transformable rotation by degrees
void SpriteObject::SetRotation(GLfloat rotation)
{
	GetComponent<pm::Transformable>()->SetRotation(rotation);
}
// Set new transformable scale by using vec2
void SpriteObject::SetScale(glm::vec2 scale)
{
	GetComponent<pm::Transformable>()->SetScale(scale);
}
// Set new transformable scare by using two values
void SpriteObject::SetScale(float scaleX, float scaleY)
{
	SetScale(glm::vec2(scaleX, scaleY));
}
// Set new transformable depth by value
void SpriteObject::SetDepth(GLfloat depth)
{
	GetComponent<pm::Transformable>()->SetDepth(depth);
}
// Set if SpriteObject is drawn or not
void SpriteObject::SetDrawState(bool state)
{
	GetComponent<pm::Drawable>()->SetDrawState(state);
}
// Set new color for SpriteObject (Red, green, blue, opacity)
void SpriteObject::SetColor(glm::vec4 color)
{
	GetComponent<pm::Color>()->SetColor(color);
}
// Get current color of spriteObject

glm::vec4 SpriteObject::GetColor()
{
	return GetComponent<pm::Color>()->GetColor();
}
// Set new Texture for SpriteObject, old one will be removed.
void SpriteObject::SetTexture(pm::Texture* texture)
{
	AddComponent(texture);
	SetTextureCoordinates(glm::vec4(0.0f, 0.0f, texture->GetTextureSize().x, texture->GetTextureSize().y));
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
// ADD GETTER
// As pixels
void SpriteObject::SetTextureCoordinates(glm::vec4 textureCoordinates)
{
	GetComponent<TextureCoordinates>()->SetTextureCoordinates(textureCoordinates);
}