#ifndef COMPONENT_H
#define COMPONENT_H

#include <typeinfo>
//#include <scene\GameEntity.h>

namespace pm
{
	class GameEntity; // ???

	class Component
	{
	public:
		
		Component() : parent(nullptr) {};
		Component(Component& component);
		Component(GameEntity* entity);
		
		void SetParent(GameEntity* entity);

		virtual ~Component() {};
		
	protected:

		GameEntity* parent;

	};
}

#endif // COMPONENT_H