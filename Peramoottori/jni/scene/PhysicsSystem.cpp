#include "PhysicsSystem.h"
#include <Box2D\Common\b2Math.h>
#include <core\Log.h>
#include <core\Passert.h>

using namespace pm;

PhysicsSystem& PhysicsSystem::Instance()
{
	static PhysicsSystem* instance = new PhysicsSystem();
	return *instance;
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::Update()
{
	if (entities.empty())
		return;

	for (std::vector<pm::GameEntity*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		Physics* physics = ValidatePhysics((*it));

		if (physics->initialised == false)
		{
			Transformable* transform = ValidateTransform((*it));
			Rectangle* rectangle = ValidateRectangle((*it));

			// Testcase to fix physics, should be remade to take original origin
			// into account later.
			rectangle->SetOrigin(rectangle->GetSize().x * 0.5f,
				rectangle->GetSize().y * 0.5f);

			glm::vec2 position = transform->GetPosition();
			physics->bodyDefinition.position.Set(position.x / SCALE, position.y / SCALE);
			physics->bodyDefinition.angle = transform->GetRotation();

			physics->body = world.CreateBody(&(physics->bodyDefinition));

			glm::vec2 size = rectangle->GetSize();
			physics->shape.SetAsBox((size.x * 0.5f) / SCALE, (size.y * 0.5f) / SCALE);

			CreateFixture(physics);

			physics->initialised = true;
		}

		UpdateEntity((*it));
	}

	world.Step(STEP, VELOC_ITERATION, POS_ITERATION);
}

void PhysicsSystem::AddGameEntity(pm::GameEntity* entity)
{
	entities.push_back(entity);
}

PhysicsSystem::PhysicsSystem() : world(b2Vec2(0.0f, 10.0f))
{
}

void PhysicsSystem::UpdateEntity(pm::GameEntity* entity)
{
	Physics* physics = ValidatePhysics(entity);
	Transformable* transform = ValidateTransform(entity);
	Rectangle* rectangle = ValidateRectangle(entity);

	//glm::vec2 size = rectangle->GetSize();
	//physics->shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);

	b2Vec2 position = physics->body->GetPosition();
	float32 angle = physics->body->GetAngle();
	transform->SetPosition(position.x * SCALE, position.y * SCALE);
	transform->SetRotation(angle * 180 / b2_pi);
}

void PhysicsSystem::CreateFixture(Physics* component, float density, float friction)
{
	component->fixture.shape = &(component->shape);
	component->fixture.density = density;
	component->fixture.friction = friction;
	component->body->CreateFixture(&(component->fixture));
}

Physics* PhysicsSystem::ValidatePhysics(pm::GameEntity* entity)
{
	Physics* physics = entity->GetComponent<Physics>();
	if (physics == nullptr)
	{
		DEBUG_WARNING(("Physics component not found."));
		ASSERT(false);
		return nullptr;
	}
	return physics;
}

Transformable* PhysicsSystem::ValidateTransform(pm::GameEntity* entity)
{
	Transformable* transform = entity->GetComponent<Transformable>();
	if (transform == nullptr)
	{
		DEBUG_WARNING(("Transformable component not found."));
		ASSERT(false);
		return nullptr;
	}
	return transform;
}

Rectangle* PhysicsSystem::ValidateRectangle(pm::GameEntity* entity)
{
	Rectangle* rectangle = entity->GetComponent<Rectangle>();
	if (rectangle == nullptr)
	{
		DEBUG_WARNING(("Rectangle component not found."));
		ASSERT(false);
		return nullptr;
	}
	return rectangle;
}