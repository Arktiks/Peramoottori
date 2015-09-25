#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <scene\Component.h>
#include <unordered_map>
#include <typeinfo>
#include <scene\Texture.h>
#include <unordered_map>

namespace pm
{

	/// \brief The base of entity component system that stores components.
	class GameEntity
	{

		using ComponentList = std::unordered_map<const std::type_info*, Component*>;

	public:
		///\brief Default constructor for GameEntity.
		GameEntity() {};

		~GameEntity();

		///\brief Add new component to the GameEntity.
		// \param Component to be added to the GameEntity.
		void AddComponent(Component* newComponent);

		
		///\brief Return desired component from GameEntity.
		//For example: 
		//ComponentClass* componentName = <ComponentClass>GetComponent();
		//Color* ColorComponent = <Color>GetComponent();
		template<typename T> T* GetComponent();

		
		///\brief Removes desired component from GameEntity.
		//For example:
		//<Color>RemoveComponent();
		template<typename T> void RemoveComponent();
	private:

		ComponentList components;

	};
}

template<typename T>
T* pm::GameEntity::GetComponent()
{
	if (components.count(&typeid(T)) != 0)
		return static_cast<T*>(components[&typeid(T)]);
	else
		return nullptr;
}

template<typename T>
void pm::GameEntity::RemoveComponent()
{
	ComponentList::const_iterator position =
		components.find(&typeid(T));
	if (position == components.end())
		return;
	components.erase(position);
}

#endif // GAMEENTITY_H