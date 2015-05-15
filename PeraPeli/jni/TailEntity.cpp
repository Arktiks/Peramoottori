#include "TailEntity.h"
#include <scene\Transformable.h>
#include <graphics\Color.h>

TailEntity::TailEntity(glm::vec2 position, float fadeTime, pm::Texture* texture) :SpriteObject(texture)
{
	this->fadeTime = fadeTime;
	GetComponent<pm::Transformable>()->SetPosition(position);
}
TailEntity::TailEntity(glm::vec2 position, float fadeTime)
{
	this->fadeTime = fadeTime;
	this->currentFadeTime = fadeTime;
}

TailEntity::~TailEntity()
{
}

bool TailEntity::Update(float time)
{
	currentFadeTime -= time;
	glm::vec4 currentColor = GetComponent<pm::Color>()->GetColor();
	currentColor.w = currentFadeTime / fadeTime;
	GetComponent<pm::Color>()->SetColor(currentColor);
	return CheckDestruction();
}

bool TailEntity::CheckDestruction()
{
	if (fadeTime < 0)
		return false;
	else
		return true;
}