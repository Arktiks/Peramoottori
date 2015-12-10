#pragma once

#include <scene\GameEntity.h>
#include <scene\Hitbox.h>
#include <string>
#include "pmScene.h"

class GameEntityFactory
{
public:
	GameEntityFactory(pmScene* scene);
	~GameEntityFactory();
	pm::GameEntity* CreateHero(glm::vec2 position, int depth, glm::vec2 size,
		glm::vec2 force, float animationFrameTime);
	pm::GameEntity* CreateRospot(glm::vec2 position, int depth, glm::vec2 size,
		glm::vec2 force);
	pm::GameEntity* CreateMovingOpaque(std::string filename, glm::vec2 position, int depth, glm::vec2 size,
		glm::vec2 force);
	pm::GameEntity* CreateButton(glm::vec2 position, int depth, glm::vec2 size);
	
private:
	// Adds transformable, rectangle, color and drawable
	void AddSpriteComponents(pm::GameEntity* gameEntity, std::string textureFilePath, glm::vec2 position, glm::vec2 scale,
		float rotation, int depth, glm::vec2 size, glm::vec4 color);
	// Adds TextureCoordinates and Animation-component.
	void AddAnimationComponents(pm::GameEntity* gameEntity, glm::vec4 textureCoordinates, float animationFrameTime, glm::vec2 frameSize,
		glm::vec2 frameAmounts, int frameAmount, int startFrame);
	
	// ONLY USE IF YOU HAVE ADDED RECTANGLE
	// SPRITECOMPONENTS ADDS RECTANGLE
	void AddInputComponents(pm::GameEntity* gameEntity);
	pmScene* scene;
};

