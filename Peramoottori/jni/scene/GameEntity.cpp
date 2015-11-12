#include "GameEntity.h"
#include <typeinfo>

pm::GameEntity::~GameEntity()
{	
	for (ComponentList::iterator it = components.begin(); it != components.begin(); it++)
		delete it->second;
	
	/* Reworking destructor.
	ComponentList::const_iterator position = components.begin();
	while (position != components.end())
	{	
		//delete position->second;
		//position++;
		//position->second = nullptr;
		//position = components.erase(position);
		//std::type_info ti1 = typeid(Texture);
		if (position->first != &typeid(Texture))
			delete position->second;

		position++;
	} */
}

void pm::GameEntity::AddComponent(Component* newComponent)
{
	RemoveComponent<Component>();
	newComponent->SetParent(this); // GameEntity* const this : cannot change what the pointer points to
	components[&typeid(*newComponent)] = newComponent;

	// If this component exists, delete it and add new one.
	// Check RemoveComponent and test later for simpler implementation
	// ComponentList::iterator componentIt  = components.find(&typeid(*newComponent));
	//if (componentIt != components.end())
	//{
	//	delete componentIt->second;
	//}
}