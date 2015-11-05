#include "Physics.h"
#include "PhysicsSystem.h"
#include "GameEntity.h"
#include <core\Log.h>
#include <core\Passert.h>

using namespace pm;

Physics::Physics() : body(nullptr), dynamic(true), initialised(false)
{
	bodyDefinition.type = b2_dynamicBody; // Need to create different construct for static objects.
}

Physics::~Physics()
{
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