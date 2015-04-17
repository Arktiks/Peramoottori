#include "Component.h"

pm::Component::Component()
{
	parent = nullptr;
}

pm::Component::Component(Component& component)
{
	parent = component.parent;
}

pm::Component::Component(GameEntity* entity)
{
	parent = entity;
}

void pm::Component::SetParent(GameEntity* entity)
{
	parent = entity;
}