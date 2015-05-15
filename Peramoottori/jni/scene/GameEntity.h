#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <scene\Component.h>
#include <unordered_map>
#include <typeinfo>
#include <scene\Texture.h>

namespace pm
{
	/// The base of entity component system that stores components.

	class GameEntity
	{

		using ComponentList = std::unordered_map < const std::type_info*, Component* >;

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
		*/
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
	// What happens if there is no component to be erased?
	components.erase(&typeid(T));
}

#endif // GAMEENTITY_H