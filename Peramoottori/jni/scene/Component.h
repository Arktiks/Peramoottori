#ifndef COMPONENT_H
#define COMPONENT_H

#include <typeinfo>

namespace pm
{
	class GameEntity;

	class Component
	{
	public:
		
		Component();
		Component(Component& component);
		Component(GameEntity* entity);
		virtual ~Component();

		void SetParent(GameEntity* entity);
		
	protected:

		GameEntity* parent;

	};
}

#endif // COMPONENT_H