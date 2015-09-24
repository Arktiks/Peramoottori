#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <scene\Component.h>
#include <unordered_map>
#include <typeinfo>
#include <scene\Texture.h>
#include <unordered_map>

namespace pm
{
	/// The base of entity component system that stores components.

	class GameEntity
	{

		using ComponentList = std::unordered_map<const std::type_info*, Component*>;

	public:

		/// Default constructor.
		GameEntity() {};

		~GameEntity();

		/// Adds a new component to GameEntity
		void AddComponent(Component* newComponent);

		/**
		* Return desired component from GameEntity.
		* For example:
		* Color* ColorComponent = <Color>GetComponent();
		*/
		template<typename T> T* GetComponent();

		/**
		* Removes desired component from GameEntity.
		* For example:
		* <Color>RemoveComponent();
		* Does not work.
		*/
		//template<typename T> void RemoveComponent();
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