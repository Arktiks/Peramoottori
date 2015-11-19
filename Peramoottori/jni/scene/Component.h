#ifndef COMPONENT_H
#define COMPONENT_H

#include <typeinfo>

namespace pm
{
	class GameEntity;

	/** \brief Base class for all components.
	*
	* Description.
	*
	* \ingroup Scene
	*/

	class Component
	{
	public:

		Component() : parent(nullptr) {};

		/** \brief Copy constuctor. */
		Component(Component& component);

		/** \brief Constructor that sets GameEntity as the components parent.
		*
		* \param[in] entity Pointer to GameEntity to be set as parent.
		*/
		Component(GameEntity* entity);
		
		/** \brief Set new parent for component.
		*
		* \param[in] entity Pointer to GameEntity to be set as parent.
		*/
		virtual void SetParent(GameEntity* entity);

		/** \brief Return handle to components GameEntity parent.
		*
		* \return GameEntity* To parent of component.
		*/
		GameEntity* GetParent() { return parent; };

		virtual ~Component() {};
		
	protected:

		GameEntity* parent;
	};
}

#endif // COMPONENT_H