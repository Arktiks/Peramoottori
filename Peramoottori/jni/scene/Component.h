#ifndef COMPONENT_H
#define COMPONENT_H

#include <scene/GameEntity.h>

namespace pm
{
	class Component
	{
	public:
		Component();
		Component(Component& component);
		Component(GameEntity* entity);
		~Component();
		
	private:
		GameEntity* parent;
	};
}

#endif // COMPONENT_H