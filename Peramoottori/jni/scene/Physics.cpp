#include "Physics.h"
#include "PhysicsSystem.h"
using namespace pm;

Physics::Physics() : Component(), body(nullptr), dynamic(true), initialised(false)
{
	bodyDefinition.type = b2_dynamicBody;
}

Physics::Physics(bool dynamic) : Component(), body(nullptr), dynamic(true), initialised(false)
{
	if(dynamic)
		SetDynamic();
	SetStatic();
}

Physics::~Physics()
{
	// Body needs to be destroyed from Box2D simulation.
	PhysicsSystem::Instance().world.DestroyBody(body); 
}

void Physics::SetDynamic()
{
	dynamic = true;
	bodyDefinition.type = b2_dynamicBody;
}

void Physics::SetStatic()
{
	dynamic = false;
	bodyDefinition.type = b2_staticBody;
}