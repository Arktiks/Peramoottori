#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <scene\Component.h>
#include <unordered_map>
#include <typeinfo>
#include <scene\Texture.h>

namespace pm
{
	class GameEntity
	{
		using ComponentList = std::unordered_map < const std::type_info*, Component* >;

	public:

		GameEntity() {};
		~GameEntity();

		void AddComponent(Component* newComponent);
		template<typename T> T* GetComponent();

		template<typename T> void RemoveComponent();

	private:
		ComponentList components;
	};
} // end namespace

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