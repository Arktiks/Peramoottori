#ifndef COMPONENT_H
#define COMPONENT_H

#include <typeinfo>
//#include <scene\GameEntity.h>

namespace pm
{
	class GameEntity; /// fore declaration of GameEntity class.

	class Component
	{
	public:

		// parenting
		/// Constructor.
		Component() : parent(nullptr) {};

		/// Constructor.
		Component(Component& component);

		/// Constructor.
		Component(GameEntity* entity);
		
		/// Sets the parent.
		void SetParent(GameEntity* entity);

		/// Return handle to components GameEntity parent.
		GameEntity*  GetParent() { return parent; };

		virtual ~Component() {};
		
	protected:

		GameEntity* parent;

	};
}

#endif // COMPONENT_H