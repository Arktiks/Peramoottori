#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <scene\GameEntity.h>
#include <Box2D\Dynamics\b2World.h>
#include <vector>
#include "Physics.h"
#include "Transformable.h"
#include <graphics\Rectangle.h>

/** \internal There is soon going to be need for general game-engine manager
* that manages all the systems. 
*/

namespace pm
{
	class PhysicsSystem
	{
	public:

		static PhysicsSystem& Instance();
		
		~PhysicsSystem();

		void Update();

		void AddGameEntity(pm::GameEntity* entity);

		void UpdateEntity(pm::GameEntity* entity);

		b2World world;

	private:

		PhysicsSystem();

		const float32 STEP = 0.017f; // 60 times per second.

		const int32 VELOC_ITERATION = 6;

		const int32 POS_ITERATION = 2;

		/*  We need to divide the pixel positions by SCALE because Box2D doesn’t use pixel coordinates.
		Instead, it uses real world measurement units. So whenever we want to specify a position in the
		Box2D world, we need to convert to coordinates into the one that Box2D uses. */
		const float SCALE = 30.0f;

		std::vector<pm::GameEntity*> entities;

		void CreateFixture(Physics* component, float density = 1.0f, float friction = 0.3f);

		Physics* ValidatePhysics(pm::GameEntity* entity);

		Transformable* ValidateTransform(pm::GameEntity* entity);

		Rectangle* ValidateRectangle(pm::GameEntity* entity);
	};
}

#endif