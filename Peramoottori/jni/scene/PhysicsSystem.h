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
	/** \brief PhysicsSystem handles initialisation and updating of Physic components.
	*
	* If GameEntity is being managed by PhysicsSystem its Transform and Rectangle components
	* are being updated according to Box2D simulation counterpart.
	*
	* By default b2World gravity is initialised with b2Vec2(0.0f, 10.0f).
	*
	* \sa http://box2d.org/
	*/

	class PhysicsSystem
	{
	public:

		static PhysicsSystem& Instance();
		
		/** \brief Default destructor
		*/
		~PhysicsSystem();

		/** \brief Initialise Physics components, update GameEntities and step world physics. */
		void Update();

		/** \brief Add GameEntity to be updated in PhysicsSystem.
		*
		* \param[in] entity Pointer to be updated GameEntity.
		*/
		void AddGameEntity(pm::GameEntity* entity);

		/** \brief b2World is the physics hub that manages memory, objects and simulation of Box2D. */
		b2World world;

		// For experimental version following variables and functions have been set public.
	public:

		PhysicsSystem();

		/** \brief Update Transform and Rectangle components based on Physics component state.
		*
		* \param[in] entity Pointer to be updated GameEntity.
		*/
		void UpdateEntity(pm::GameEntity* entity);

		const float32 STEP = 0.017f; // 60 times per second.

		/** \brief Velocity iteration amount for Box2D constraint solver.
		*
		* In velocity phase Box2D solver computes the impulses necessary for the bodies to move correctly.
		*/
		const int32 VELOC_ITERATION = 6;

		/** \brief Positio iteration amount for Box2D constraint solver.
		*
		* In position phase Box2D solver adjusts the positions of the bodies to reduce overlap and joint detachment. 
		*/
		const int32 POS_ITERATION = 2;

		/** \brief Scale between Box2D simulation measurements and pixel coordinates.
		*
		* We need to divide the pixel positions by SCALE because Box2D doesn't use pixel coordinates.
		* Instead, it uses real world measurement units. So whenever we want to specify a position in the
		* Box2D world, we need to convert to coordinates into the one that Box2D uses.
		*/
		const float SCALE = 30.0f;

		/** \brief GameEntities which physics are being updated. 
		*
		* \sa PhysicsSystem::AddGameEntity
		*/
		std::vector<pm::GameEntity*> entities;

		/** \brief Create fixture for Physics component.
		*
		* \param[in] component handle for which fixtures are initialised.
		* \param[in] density is used to compute the mass properties of the parent body.
		* \param[in] friction is used to make objects slide along each other realistically.
		*/
		void CreateFixture(Physics* component, float density = 1.0f, float friction = 0.5f);
		
		//@{
		/** \brief Validate presence of necessary component used to update physics.
		*
		* \return Pointer to component.
		*/
		Physics* ValidatePhysics(pm::GameEntity* entity);
		Transformable* ValidateTransform(pm::GameEntity* entity);
		Rectangle* ValidateRectangle(pm::GameEntity* entity);
		//@}
	};
}

#endif