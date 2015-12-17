#pragma once
#include <vector>
#include "Physics.h"
#include <scene\GameEntity.h>
#include <scene\Transformable.h>
#include <graphics\Rectangle.h>
#include <scene\Name.h>

class PhysicsManager
{
public:
	PhysicsManager(){ physicsUpdateRate = 0.1; physicsTime = 0; };
	PhysicsManager(glm::vec2 worldLimits, float physicsUpdateRate);
	~PhysicsManager();
	
	void AddPhysics(pm::GameEntity* target);
	void RemoveGameEntity();
	void Update(float time);

	void UpdatePhysics(Physics* physics);

	// Peri ja anna käyttäjän tehdä nämä itse.
	void AddForceToHeroes(glm::vec2 force);
	void UpdateWave(Physics* physics);
	
	glm::vec2 SetPosition(Physics* physics);
	
	void KeepInsideScreen(Physics* physics);
	void RepeatMovement(Physics* physics);
	void TargetCenter(Physics* physics);

	glm::vec2 CheckLimits(glm::vec2 position);

private:
	std::vector<Physics*> physicsVector;
	float physicsUpdateRate;
	float physicsTime;
	// Peri ja anna käyttäjän tehdä nämä itse.
	glm::vec2 worldLimits;
};

