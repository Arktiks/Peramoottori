#include "PhysicsManager.h"
#include <glm\glm.hpp>

PhysicsManager::PhysicsManager(glm::vec2 worldLimits, float physicsUpdateRate)
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
	if (target->GetComponent<pm::Name>() == nullptr)
	{
		target->AddComponent(NEW pm::Name("default"));
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
	if (physics->GetParent()->GetComponent<pm::Name>()->GetName() == "hero")
	{
		SetPosition(physics);
		KeepInsideScreen(physics);
	}
	else if (physics->GetParent()->GetComponent<pm::Name>()->GetName() == "rospot")
	{
		TargetCenter(physics);
		SetPosition(physics);
		RepeatMovement(physics);
	}
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

void PhysicsManager::RepeatMovement(Physics* physics)
{
	pm::Transformable* transformable = physics->GetParent()->GetComponent<pm::Transformable>();
	pm::Rectangle* rectangle = physics->GetParent()->GetComponent<pm::Rectangle>();
	glm::vec2 respond = CheckLimits(transformable->GetPosition());

	glm::vec2 currentPosition = transformable->GetPosition();

	if (respond.x != 0)
	{
		// OVER LIMITS
		if (respond.x == 1)
		{
			// IF OBJECT'S DIRECTION IS AWAY FROM LIMITS
			if (physics->speed.x > 0)
			{
				physics->speed.x = 0;
				currentPosition.x = -rectangle->GetSize().x;
			}
		}
		// UNDER LIMITS
		else if (respond.x == -1)
		{
			// IF OBJECT'S DIRECTION IS AWAY FROM LIMITS
			if (physics->speed.x < 0)
			{
				physics->speed.x = 0;
				currentPosition.x = worldLimits.x + rectangle->GetSize().x;
			}
		}
	}

	if (respond.y != 0)
	{
		// OVER LIMITS
		if (respond.y == 1)
		{
			// IF OBJECT'S DIRECTION IS AWAY FROM LIMITS
			if (physics->speed.y > 0)
			{
				physics->speed.y = 0;
				currentPosition.y = -rectangle->GetSize().y;
			}
		}
		// UNDER LIMITS
		else if (respond.y == -1)
		{
			// IF OBJECT'S DIRECTION IS AWAY FROM LIMITS
			if (physics->speed.y < 0)
			{
				physics->speed.y = 0;
				currentPosition.y = worldLimits.y + rectangle->GetSize().y;		
			}
		}
	}
	transformable->SetPosition(currentPosition);

}

void PhysicsManager::TargetCenter(Physics* physics)
{
	pm::Transformable* transformable = physics->GetParent()->GetComponent<pm::Transformable>();
	pm::Transformable* targetTransformable = physicsVector[3]->GetParent()->GetComponent<pm::Transformable>();
	glm::vec2 target = glm::vec2(targetTransformable->GetPosition());
	glm::vec2 position = transformable->GetPosition();

	glm::vec2 forceDir = target - position;
	
	glm::vec2 normalizedForce = glm::vec2(forceDir.x / (sqrt(pow(forceDir.x, 2) + pow(forceDir.y, 2))),
		forceDir.y / (sqrt(pow(forceDir.x, 2) + pow(forceDir.y, 2))));

	physics->force = physics->force + normalizedForce * glm::vec2(0.01,0.01);
}

glm::vec2 PhysicsManager::CheckLimits(glm::vec2 position)
{
	glm::vec2 respond;
	// Check if position is more than limits; respond with 1
	if (position.x > worldLimits.x)
	{
		respond.x = 1;
	}
	// Check if position is less than limits; respond with -1
	else if (position.x < 0)
	{
		respond.x = -1;
	}
	// else respond that it is within limits (0)
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
