#include "PhysicsSystem.h"
#include <Box2D\Common\b2Math.h>
#include "Physics.h"

using namespace pm;

PhysicsSystem& PhysicsSystem::Instance()
{
	static PhysicsSystem* instance = new PhysicsSystem();
	return *instance;
}

PhysicsSystem::PhysicsSystem() : world(b2Vec2(0.0f, -10.0f))
{
	
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::Update()
{
	world.Step(STEP, VELOC_ITERATION, POS_ITERATION);

	/*for(std::vector<pm::GameEntity*>::iterator it = entities.begin(); it != entities.end(); it++)
		(*it)->GetComponent<Physics>()->Update();*/
}

void PhysicsSystem::AddGameEntity(pm::GameEntity* entity)
{
	entities.push_back(entity);
}