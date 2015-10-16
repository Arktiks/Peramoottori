#include "Physics.h"
#include "PhysicsSystem.h"
#include "GameEntity.h"

#include <core\Log.h>
#include <core\Passert.h>

using namespace pm;

Physics::Physics() : body(nullptr), dynamic(true)
{
	bodyDefinition.type = b2_dynamicBody; // Need to create different construct for static objects.

	/* Set starting size - doesn't take scale into account! */
	Rectangle* rectangle = Rectangle();
	glm::vec2 size = rectangle->GetSize();
	shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);

	/* Set starting position. */
	Transformable* transform = Transform();
	glm::vec2 position = transform->GetPosition();
	bodyDefinition.position.Set(position.x, position.y);

	/* Hardcoded fixture settings. */
	fixture.shape = &shape;
	fixture.density = 1.0f;
	fixture.friction = 0.3f;

	body->CreateFixture(&fixture);
	body = PhysicsSystem::Instance().world.CreateBody(&bodyDefinition);
}

Physics::~Physics()
{
}

void Physics::Update()
{
	/* Update possible size changes. Can be optimized to be more
	* lightweight if there is performance problems. */
	Rectangle* rectangle = Rectangle();
	glm::vec2 size = rectangle->GetSize();
	shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	
	/* Update positions and angle. */
	Transformable* transform = Transform();
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();
	transform->SetPosition(position.x, position.y);
	transform->SetRotation(angle);
}

Transformable* Physics::Transform()
{
	Transformable* transform = parent->GetComponent<Transformable>();
	ASSERT_NEQUAL(transfrom, nullptr);
	return transform;
}

Rectangle* Physics::Rectangle()
{
	Rectangle* rectangle = parent->GetComponent<Rectangle>();
	ASSERT_NEQUAL(rectangle, nullptr);
	return rectangle;
}