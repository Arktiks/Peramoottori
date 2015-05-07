#include "PhysicComponent.h"


PhysicComponent::PhysicComponent()
{
	velocity = glm::vec2(0.0f, 0.0f);
	position = glm::vec2(0.0f, 0.0f);
}


PhysicComponent::~PhysicComponent()
{
}

void PhysicComponent::SetVelocity(glm::vec2 newVelocity)
{
	velocity = newVelocity;
}
void PhysicComponent::SetPosition(glm::vec2 newPosition)
{
	position = newPosition;
}
glm::vec2 PhysicComponent::GetVelocity()
{
	return velocity;
}
glm::vec2 PhysicComponent::GetPosition()
{
	return position;
}