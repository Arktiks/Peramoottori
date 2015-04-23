#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <scene\Component.h>
#include <unordered_map>
#include <typeinfo>

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

#endif // GAMEENTITY_H