#ifndef PHYSICS_H
#define PHYSICS_H

#include "Component.h"
#include <Box2D\Dynamics\b2Body.h>
#include <Box2D\Collision\Shapes\b2PolygonShape.h>
#include <Box2D\Dynamics\b2Fixture.h>

#include <scene\Transformable.h>
#include <graphics\Rectangle.h>

/** \internal Currently Transform and Rectangle components
* need to be created before Physics component. */

namespace pm
{
	class Physics : public Component
	{
	public:

		Physics();
		~Physics();

		void Update();

		// Need to check later if these functions need further changes.
		void SetDynamic();
		void SetStatic();

	private:

		b2BodyDef bodyDefinition;

		b2Body* body;

		b2PolygonShape shape;

		b2FixtureDef fixture;

		bool dynamic;

		bool initialised;

		//pm::Transformable* GetTransform();

		//pm::Rectangle* GetRectangle();
	};
}

#endif