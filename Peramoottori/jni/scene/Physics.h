#ifndef PHYSICS_H
#define PHYSICS_H

#include "Component.h"
#include <Box2D\Dynamics\b2Body.h>
#include <Box2D\Collision\Shapes\b2PolygonShape.h>
#include <Box2D\Dynamics\b2Fixture.h>

namespace pm
{
	class Physics : public Component
	{
	public:

		Physics();
		~Physics();

		void Update();

	private:

		b2BodyDef bodyDefinition;

		b2Body* body;

		b2PolygonShape shape;

		b2FixtureDef fixture;

		bool dynamic;
	};
}

#endif