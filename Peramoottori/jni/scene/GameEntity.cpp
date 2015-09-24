#include "GameEntity.h"
#include <typeinfo>

pm::GameEntity::~GameEntity()
{
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
	}
//for (auto it = components.begin(); it != components.end(); ++it)
//{	
//	delete it->second;
//}
}

void pm::GameEntity::AddComponent(Component* newComponent)
{
	// If this component exists, delete it and add new one.
	// Check RemoveComponent and test later for simpler implementation
	//ComponentList::iterator componentIt  = components.find(&typeid(*newComponent));


	//if (componentIt != components.end())
	//{
	//	delete componentIt->second;
	//}

	RemoveComponent<Component>();
	newComponent->SetParent(this);
	components[&typeid(*newComponent)] = newComponent;
}