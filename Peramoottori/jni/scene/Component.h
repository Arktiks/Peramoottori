#ifndef COMPONENT_H
#define COMPONENT_H

#include <scene/GameEntity.h>

namespace pm
{
	class Component
	{
	public:
		virtual void update(){};
	
	private:
		GameEntity* parent;
	};
}

#endif // COMPONENT_H