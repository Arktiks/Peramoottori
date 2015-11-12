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

		friend class PhysicsSystem;

	public:

		Physics();
		~Physics();

		// Need to check later if these functions need further changes.
		void SetDynamic();
		void SetStatic();

	private:

		/* BodyDef defines the initial position of the body and the
		type of the body (static, dynamic or kinematic). Static basically
		means that the body may never move. Dynamic means that the body
		can interact with other bodies. Kinematic means the body can move
		but it will not be affected by other bodies (for example, an elevator perhaps). */
		b2BodyDef bodyDefinition;

		b2Body* body;

		/* Shape of b2Body. Peramoottori only supports rectangles currently. */
		b2PolygonShape shape;

		/* Properties of b2Body. */
		b2FixtureDef fixture;

		bool dynamic;

		bool initialised;
	};
}

#endif