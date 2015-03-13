#include "scene\Component.h"

pm::Component::Component()
{
	parent = nullptr;
}

pm::Component::Component(Component& component)
{
	this->parent = component.parent;
}

pm::Component::Component(GameEntity* entity)
{
	parent = entity;
}

pm::Component::~Component()
{
	delete parent;
}