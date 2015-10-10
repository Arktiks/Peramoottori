#include "Physics.h"
#include "PhysicsSystem.h"
#include "GameEntity.h"

#include <graphics\Rectangle.h>
#include <core\Log.h>

using namespace pm;

Physics::Physics() : body(nullptr), dynamic(true)
{
	bodyDefinition.type = b2_dynamicBody;

	fixture.shape = &shape;
	fixture.density = 1.0f;
	fixture.friction = 0.3f;

	body = PhysicsSystem::Instance().world.CreateBody(&bodyDefinition);
	body->CreateFixture(&fixture);
}

Physics::~Physics()
{
}

void Physics::Update()
{
	Rectangle* rectangle = parent->GetComponent<Rectangle>();

	if( rectangle == nullptr)
	{
		DEBUG_WARNING(("Trying to update Physics on GameEntity without Shape."));
		return;
	}
	else
	{
		glm::vec2 size = rectangle->GetSize();

		shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	}
}