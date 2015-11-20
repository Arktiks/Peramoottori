#include "PhysicsManager.h"


PhysicsManager::PhysicsManager(glm::vec2 worldLimits, float physicUpdateRate)
{
	this->worldLimits = worldLimits;
	this->physicsUpdateRate = physicsUpdateRate;
	physicsTime = 0;
}


PhysicsManager::~PhysicsManager()
{
}
void PhysicsManager::AddGameEntity(pm::GameEntity* gameEntity)
{
	if (gameEntity->GetComponent<pm::Transformable>() == nullptr)
	{
		gameEntity->AddComponent(NEW pm::Transformable);
	}
	if (gameEntity->GetComponent<pm::Rectangle>() == nullptr)
	{
		gameEntity->AddComponent(NEW pm::Rectangle);
	}
	if (gameEntity->GetComponent<Physics>() == nullptr)
	{
		gameEntity->AddComponent(NEW Physics);
	}
	gameEntityVector.push_back(gameEntity);
}
void PhysicsManager::Update(float time)
{
	physicsTime += time;
	if (physicsTime > physicsUpdateRate)
	{
		for (int i = 0; i < gameEntityVector.size(); i++)
		{
			UpdateGameObject(gameEntityVector[i]);
		}
	}
}
void PhysicsManager::UpdateGameObject(pm::GameEntity* entity)
{
	Physics* physics = entity->GetComponent<Physics>();
	pm::Transformable* transformable = entity->GetComponent<pm::Transformable>();

	SetPosition(entity);
	KeepInsideScreen(entity);

}
glm::vec2 PhysicsManager::SetPosition(pm::GameEntity* entity)
{
	Physics* physics = entity->GetComponent<Physics>();
	pm::Transformable* transformable = entity->GetComponent<pm::Transformable>();
	glm::vec2 currentPosition = transformable->GetPosition();
	glm::vec2 currentSpeed = physics->speed;

	currentPosition.x += currentSpeed.x;
	currentPosition.y += currentSpeed.y;
	transformable->SetPosition(currentPosition);
}

void PhysicsManager::KeepInsideScreen(pm::GameEntity* entity)
{
	Physics* physics = entity->GetComponent<Physics>();
	pm::Transformable* transformable = entity->GetComponent<pm::Transformable>();

	glm::vec2 respond = CheckLimits(transformable->GetPosition());
	// OVER LIMITS
	glm::vec2 currentPosition = transformable->GetPosition();
	if (respond.x != 0)
	{
		if (respond.x == 1)
		{
			physics->speed.x = physics->speed.x * -1;
			currentPosition.x = worldLimits.x;
		}
		// UNDER LIMITS
		else if (respond.x == -1)
		{
			physics->speed.x = physics->speed.x * -1;
			currentPosition.x = 0;
		}
	}

	if (respond.y != 0)
	{
		// OVER LIMITS
		if (respond.y == 1)
		{
			physics->speed.y = physics->speed.y * -1;
			currentPosition.y = worldLimits.y;
		}
		// UNDER LIMITS
		else if (respond.y == -1)
		{
			physics->speed.y = physics->speed.y * -1;
			currentPosition.y = worldLimits.y;
		}
	}
	transformable->SetPosition(currentPosition);

}
glm::vec2 PhysicsManager::CheckLimits(glm::vec2 position)
{
	glm::vec2 respond;
	if (position.x > worldLimits.x)
	{
		respond.x = 1;
	}
	else if (position.x < 0)
	{
		respond.x = -1;
	}
	else
	{
		respond.x = 0;
	}

	if (position.y > worldLimits.y)
	{
		respond.y = 1;
	}
	else if (position.y < 0)
	{
		respond.y = -1;
	}
	else
	{
		respond.y = 0;
	}
	return respond;
}
