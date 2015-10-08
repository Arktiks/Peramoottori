#ifndef COMPONENT_H
#define COMPONENT_H

#include <typeinfo>

namespace pm
{
	///\brief Component class parent that is inherited for all components.
	//\ingroup Scene
	class GameEntity;

	class Component
	{
	public:

		
		///\brief Default constructor for Components.
		Component() : parent(nullptr) {};

		///\brief Copy constuctor for Components
		// \param[in] component Component to be copied.
		Component(Component& component);

		///\brief Constructor that sets GameEntity as the component's parent.
		// \param[in] entity Entity to be set as parent for the Component.
		Component(GameEntity* entity);
		
		
		///Set new parent for component
		// \param[in] entity Entity that will be set as the Component's Parent.
		void SetParent(GameEntity* entity);

		
		///Return handle to components GameEntity parent.
		// \return Returns a pointer to the parent of the Component.
		GameEntity*  GetParent() { return parent; };

		virtual ~Component() {};
		
	protected:

		GameEntity* parent;
	};
}

#endif // COMPONENT_H