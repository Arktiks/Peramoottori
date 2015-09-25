#ifndef COMPONENT_H
#define COMPONENT_H

#include <typeinfo>

namespace pm
{
	/** \brief Component class parent that is inherited for all components.
	* 
	* 
	* \ingroup Scene
	*/
	class GameEntity;

	class Component
	{
	public:

		/**
		* Little lost component
		*/
		Component() : parent(nullptr) {};

		/** \brief Copy constuctor
		* 
		*/
		Component(Component& component);

		/** \brief Set GameEntity as component's parent
		* 
		*/
		Component(GameEntity* entity);
		
		/**
		* Set new parent for component
		*/
		void SetParent(GameEntity* entity);

		/**
		* Return handle to components GameEntity parent.
		*/
		GameEntity*  GetParent() { return parent; };

		virtual ~Component() {};
		
	protected:

		GameEntity* parent;
	};
}

#endif // COMPONENT_H