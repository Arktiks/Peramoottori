#include "Physics.h"
#include "PhysicsSystem.h"
#include "GameEntity.h"

#include <core\Log.h>
#include <core\Passert.h>

using namespace pm;

Physics::Physics() : body(nullptr), dynamic(true), initialised(false)
{
	bodyDefinition.type = b2_dynamicBody; // Need to create different construct for static objects.

	/* Set starting size - doesn't take scale into account! */
	//Rectangle* rectangle = GetRectangle();
	//glm::vec2 size = rectangle->GetSize();
	glm::vec2 size = parent->GetComponent<Rectangle>()->GetSize();
	shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);

	/* Set starting position. */
	//Transformable* transform = GetTransform();
	//glm::vec2 position = transform->GetPosition();
	glm::vec2 position = parent->GetComponent<Transformable>()->GetPosition();
	bodyDefinition.position.Set(position.x, position.y);
	//bodyDefinition.angle = transform->GetRotation();
	bodyDefinition.angle = parent->GetComponent<Transformable>()->GetRotation();

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
	//Rectangle* rectangle = GetRectangle();
	//glm::vec2 size = rectangle->GetSize();
	glm::vec2 size = parent->GetComponent<Rectangle>()->GetSize();
	shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	
	/* Update positions and angle. */
	//Transformable* transform = GetTransform();
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();
	//transform->SetPosition(position.x, position.y);
	//transform->SetRotation(angle);
	parent->GetComponent<Transformable>()->SetPosition(position.x, position.y);
	parent->GetComponent<Transformable>()->SetRotation(angle);
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

///// GetComponent is generating errors.
/*Transformable* Physics::GetTransform()
{
	Transformable* transform = parent->GetComponent<Transformable>();
	//ASSERT_EQUAL(transform, nullptr);
	if(transform == nullptr)
		DEBUG_WARNING(("Physics component using null Transform!"));

	return transform;
}

Rectangle* Physics::GetRectangle()
{
	Rectangle* rectangle = parent->GetComponent<Rectangle>();
	//ASSERT_EQUAL(rectangle, nullptr);
	if(rectangle == nullptr)
		DEBUG_WARNING(("Physics component using null Rectangle!"));

	return rectangle;
}*/