#ifndef COMPONENT_H
#define COMPONENT_H

#include <typeinfo>

namespace pm
{
	class GameEntity;

	/** \brief Base class for all components.
	*
	* Virtual base class for all components to allow GameEntities having all components in same map
	*
	* \ingroup Scene
	*/

	class Component
	{
	public:
		
		/** \brief Default constructor.
		*/
		Component() : parent(nullptr) {};

		/** \brief Copy constuctor. */
		Component(Component& component);

		/** \brief Constructor that sets GameEntity as the components parent.
		*
		* \param[in] entity Pointer to GameEntity to be set as parent.
		*/
		Component(GameEntity* entity);
		
		/** \brief Set new parent for component.
		* Virtual function to allow automatic actions when adding a component
		* to a GameEntity (example class Sprite : public Component)
		* \param[in] entity Pointer to GameEntity to be set as parent.
		*/
		virtual void SetParent(GameEntity* entity);

		/** \brief Return handle to components GameEntity parent.
		*
		* \return GameEntity* To parent of component.
		*/
		GameEntity* GetParent() { return parent; };

		/** \brief Virtual destructor.
		* Component has a virtual destructor to enable the Run Time Type Identification
		* of its' child classes.
		*/
		virtual ~Component() {};
		
	protected:

		GameEntity* parent;
	};
}

#endif // COMPONENT_H