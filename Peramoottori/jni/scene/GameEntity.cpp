#include "GameEntity.h"

pm::GameEntity::~GameEntity()
{
	ComponentList::iterator it = components.begin();
	while (it != components.end())
	{
		 //Check later
		if (&typeid(*it) != &typeid(pm::Texture))
	{	
		it = components.erase(it);
	}
		else
		{
			delete it->first;
			delete it->second;
			it->second = nullptr;
			it = components.erase(it);
		}
	}
}

void pm::GameEntity::AddComponent(Component* newComponent)
{
	// If this component exists, delete it and add new one.
	// Check RemoveComponent and test later for simpler implementation
	ComponentList::iterator componentIt  = components.find(&typeid(*newComponent));

	if (componentIt != components.end())
	{
		//delete componentIt->first;
		//delete componentIt->second;//
		//componentIt->second = nullptr;
	}

	newComponent->SetParent(this);
	components[&typeid(*newComponent)] = newComponent;
}