#include <scene\GameEntity.h>

pm::GameEntity::~GameEntity()
{
	for (ComponentList::iterator it = components.begin(); it != components.end();it++)
	{
		delete it->first;
		delete it->second;
	}
	components.clear();
}

void pm::GameEntity::AddComponent(Component* newComponent)
{
	newComponent->SetParent(this);
	components[&typeid(*newComponent)] = newComponent;
}