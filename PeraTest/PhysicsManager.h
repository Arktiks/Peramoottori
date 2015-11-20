#pragma once
#include <vector>
#include "Physics.h"
#include <scene\GameEntity.h>
#include <scene\Transformable.h>
#include <graphics\Rectangle.h>

class PhysicsManager
{
public:
	PhysicsManager(){ physicsUpdateRate = 0.1; physicsTime = 0; };
	PhysicsManager(glm::vec2 worldLimits, float physicUpdateRate);
	~PhysicsManager();
	
	void AddGameEntity(pm::GameEntity* gameEntity);
	void RemoveGameEntity();
	void Update(float time);
	void UpdateGameObject(pm::GameEntity* entity);
	glm::vec2 SetPosition(pm::GameEntity* entity);
	void KeepInsideScreen(pm::GameEntity* entity);
	glm::vec2 CheckLimits(glm::vec2 position);

private:
	std::vector<pm::GameEntity*> gameEntityVector;
	float physicsUpdateRate;
	float physicsTime;
	glm::vec2 worldLimits;
};

