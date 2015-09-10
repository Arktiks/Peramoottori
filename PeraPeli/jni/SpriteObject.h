#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H


#include <scene\GameEntity.h>
#include <scene\Texture.h>
#include <glm\common.hpp>

// For debugging
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>
//

class SpriteObject:public pm::GameEntity
{
public:
	SpriteObject();
	SpriteObject(pm::Texture* texture);
	~SpriteObject();
	virtual void Update(float deltaTime);

	void AddPhysics();
	void SetVelocity(glm::vec2 velocity);
	glm::vec2 GetVelocity();

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

	
	glm::vec2 GetPosition();
	glm::vec2 GetSize();
	glm::vec2 GetOrigin();
	glm::vec4 GetColor();

	GLfloat GetRotation();
	bool done;

	// Update function for child classes

};

#endif