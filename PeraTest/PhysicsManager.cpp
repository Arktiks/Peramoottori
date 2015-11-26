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

void PhysicsManager::AddPhysics(pm::GameEntity* target)
{
	if (target->GetComponent<pm::Transformable>() == nullptr)
	{
		target->AddComponent(NEW pm::Transformable);
	}
	if (target->GetComponent<pm::Rectangle>() == nullptr)
	{
		target->AddComponent(NEW pm::Rectangle);
	}
	if (target->GetComponent<Physics>() == nullptr)
	{
		Physics* physics = NEW Physics;
		target->AddComponent(physics);
		physicsVector.push_back(physics);
	}
	physicsVector.push_back(target->GetComponent<Physics>());
}


void PhysicsManager::Update(float time)
{
	physicsTime += time;
	if (physicsTime > physicsUpdateRate)
	{
		for (int i = 0; i < physicsVector.size(); i++)
		{
			UpdatePhysics(physicsVector[i]);
		}
		physicsTime = 0;
	}
}

void PhysicsManager::UpdatePhysics(Physics* physics)
{
	SetPosition(physics);
	KeepInsideScreen(physics);
}

glm::vec2 PhysicsManager::SetPosition(Physics* physics)
{
	pm::Transformable* transformable = physics->GetParent()->GetComponent<pm::Transformable>();
	glm::vec2 currentPosition = transformable->GetPosition();
	glm::vec2 currentSpeed = physics->speed;
	glm::vec2 currentForce = physics->force;

	// Add current force to current speed.
	currentSpeed += currentForce;
	// Add current speed to current positions.
	currentPosition.x += currentSpeed.x;
	currentPosition.y += currentSpeed.y;
	// Set transformable position accordingly.
	transformable->SetPosition(currentPosition);

	// Set force to zero so it wont be applied twice to speed.
	physics->force.x = 0; physics->force.y = 0;
	// Set speed to current speed.
	physics->speed = currentSpeed;
}

void PhysicsManager::KeepInsideScreen(Physics* physics)
{
	pm::Transformable* transformable = physics->GetParent()->GetComponent<pm::Transformable>();
	glm::vec2 respond = CheckLimits(transformable->GetPosition());

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
