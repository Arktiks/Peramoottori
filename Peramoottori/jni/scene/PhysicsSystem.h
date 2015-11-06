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
*
* Physics component changes Rectangle components origin.
*/

namespace pm
{
	class PhysicsSystem
	{
	public:

		static PhysicsSystem& Instance();
		
		~PhysicsSystem();

		/** \brief Update GameEntities and step world physics.
		*
		* ---
		*/
		void Update();

		/** \brief Add GameEntity to be updated in PhysicsSystem.
		*
		* ---
		*/
		void AddGameEntity(pm::GameEntity* entity);

		b2World world;

	private:

		PhysicsSystem();

		/** \brief Update Transform and Rectangle components based on Physics component state.
		*
		* ---
		*/
		void UpdateEntity(pm::GameEntity* entity);

		const float32 STEP = 0.017f; // 60 times per second.

		const int32 VELOC_ITERATION = 6;

		const int32 POS_ITERATION = 2;

		/*  We need to divide the pixel positions by SCALE because Box2D doesn’t use pixel coordinates.
		Instead, it uses real world measurement units. So whenever we want to specify a position in the
		Box2D world, we need to convert to coordinates into the one that Box2D uses. */
		const float SCALE = 30.0f;

		std::vector<pm::GameEntity*> entities;

		/** \brief Create fixture for Physics component.
		*
		* ---
		*/
		void CreateFixture(Physics* component, float density = 1.0f, float friction = 0.5f);

		/* Validate presence of necessary components before updating Physics. */
		Physics* ValidatePhysics(pm::GameEntity* entity);
		Transformable* ValidateTransform(pm::GameEntity* entity);
		Rectangle* ValidateRectangle(pm::GameEntity* entity);
	};
}

#endif