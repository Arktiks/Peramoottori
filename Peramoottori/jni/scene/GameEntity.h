#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <scene\Component.h>
#include <unordered_map>
#include <typeinfo>
#include <unordered_map>

namespace pm
{

	/** \brief GameEntity stores components that detail its functionality.
	*
	* Description.
	*
	* \ingroup Scene
	*/

	class GameEntity
	{

		using ComponentList = std::unordered_map<const std::type_info*, Component*>;

	public:

		/** \brief Default constructor. 
		*
		* By default GameEntity stores no components.
		*/
		GameEntity() {};

		/** \brief Default destructor
		*/
		~GameEntity();

		/** \brief Add new component to GameEntity.
		*
		* More details.
		*
		* \param[in] newComponent pointer to Component to be added.
		*/
		void AddComponent(Component* newComponent);

		/** \brief Return desired component from GameEntity.
		*
		* \return Pointer to Component.
		* \return nullptr if Component was not found.
		*
		* \note Color* example = GetComponent<Color>();
		*/
		template<typename T> T* GetComponent();

		/**\brief Removes desired component from GameEntity.
		*
		* \note RemoveComponent<Color>();
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
	ComponentList::iterator it = components.find(&typeid(T));
	if (it != components.end())
	{
		delete it->second;
		components.erase(it);
	}

	/* Remove rework.
	ComponentList::const_iterator position = components.find(&typeid(T));
	if (position == components.end())
		return;
	components.erase(position); */
}



#endif // GAMEENTITY_H