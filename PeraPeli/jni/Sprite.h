#pragma once
#include "scene\GameEntity.h"
#include "scene\Texture.h"
#include <glm\common.hpp>

// For debugging
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>
//

class Sprite
{
public:
	Sprite();
	Sprite(pm::Texture* texture);
	~Sprite();

	void SetPosition(glm::vec2 position);
	void SetPosition(float positionX, float positionY);

	void SetSize(glm::vec2 size);
	void SetSize(float width, float height);

	void SetOrigin(glm::vec2 origin);
	void SetOrigin(float originX, float originY);

	void SetScale(glm::vec2 scale);
	void SetScale(float scaleX, float scaleY);

	void SetRotation(float rotation);
	void SetDepth(float depth);
	void SetDrawState(bool state);
	void SetColor(glm::vec4 color);
	void SetTexture(pm::Texture* texture);
	pm::GameEntity* GetGameEntity(){ return &gameEntity; }
	glm::vec2 GetPosition();

private:
	pm::GameEntity gameEntity;
};

