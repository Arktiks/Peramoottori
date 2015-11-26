#include "Physics.h"
#include <scene\GameEntity.h>
#include <graphics\Rectangle.h>
#include <scene\Transformable.h>

Physics::Physics()
{
	speed = glm::vec2(0, 0);
	force = glm::vec2(0, 0);
}
Physics::Physics(glm::vec2 speed, glm::vec2 force)
{
	this->speed = speed;
	this->force = force;
}


Physics::~Physics()
{
}

void Physics::SetParent(pm::GameEntity* entity)
{
	parent = entity;
	if(parent->GetComponent<pm::Transformable>() == nullptr)
	parent->AddComponent(NEW pm::Transformable());

	if (parent->GetComponent<pm::Rectangle>() == nullptr)
		parent->AddComponent(NEW pm::Rectangle());
}