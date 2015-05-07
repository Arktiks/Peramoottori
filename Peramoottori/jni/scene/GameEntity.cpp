#include "GameEntity.h"


pm::GameEntity::~GameEntity()
{
	for (ComponentList::iterator it = components.begin(); it != components.end();)
	{
		if (it->first->name() != "Texture")
		{
			delete it->second;
			delete it->first;
			it->second = nullptr;
		}

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
		delete componentIt->first;
		delete componentIt->second;//
		componentIt->second = nullptr;
	}
	newComponent->SetParent(this);
	components[&typeid(*newComponent)] = newComponent;
}