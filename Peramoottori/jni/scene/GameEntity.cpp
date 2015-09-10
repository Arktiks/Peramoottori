#include "GameEntity.h"

pm::GameEntity::~GameEntity()
{
	ComponentList::iterator it = components.begin();
	while (it != components.end())
	{
		delete it->second;
		it->second = nullptr;
		it = components.erase(it);
	}
}

void pm::GameEntity::AddComponent(Component* newComponent)
{
	// If this component exists, delete it and add new one.
	// Check RemoveComponent and test later for simpler implementation
	ComponentList::iterator componentIt  = components.find(&typeid(*newComponent));

	if (componentIt != components.end())
	{
		delete componentIt->second;
	}

	newComponent->SetParent(this);
	components[&typeid(*newComponent)] = newComponent;
}