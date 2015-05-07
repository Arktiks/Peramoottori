#include "GameEntity.h"

pm::GameEntity::~GameEntity()
{
	for (ComponentList::iterator it = components.begin(); it != components.end();it++)
	{
		delete it->second;
		delete it->first;
	}
	components.clear();
}

void pm::GameEntity::AddComponent(Component* newComponent)
{
	// If this component exists, delete it and add new one.
	// Check RemoveComponent and test later for simpler implementation
	ComponentList::iterator componentIt  = components.find(&typeid(*newComponent));
	if (componentIt != components.end())
	{
		delete componentIt->first;
		delete componentIt->second;
	}
	newComponent->SetParent(this);
	components[&typeid(*newComponent)] = newComponent;
}