#ifndef PHYSICS_H
#define PHYSICS_H

#include "Component.h"
#include <Box2D\Dynamics\b2Body.h>
#include <Box2D\Collision\Shapes\b2PolygonShape.h>
#include <Box2D\Dynamics\b2Fixture.h>

/** \internal Currently Transform and Rectangle components
* need to be created before Physics component.
*
* Physics component is highly experimental!
*/

namespace pm
{
	/** \brief Experimental Physics component for GameEntities.
	*
	* At its current state Physics component can be used to make rectangles that are
	* affected by gravity and other GameEntities with Physics component.
	*
	* Should user wish to use more complex funtions all variables of this component
	* have been left public.
	*
	* \warning Attached GameEntity should contain Transform and Rectangle components.
	* Otherwise unexpected behavior may occur.
	*
	* \sa http://box2d.org/
	*/

	class Physics : public Component
	{

		// friend class PhysicsSystem; Currently unnecessary.

	public:

		/** By default Physics component is set dynamic. */
		Physics();

		/** \param[in] dynamic False if component should be static. */
		Physics(bool dynamic);
		~Physics();

		// Need to check later if these functions need further changes.
		void SetDynamic();
		void SetStatic();

		// For experimental version following variables have been set public.
	public:

		/** \brief BodyDef defines initial position of b2Body and
		* type of the b2Body (static, dynamic or kinematic).
		*
		* Static means that the body may never move. Dynamic means that the body
		* can interact with other bodies. Kinematic means the body can move
		* but it will not be affected by other bodies.
		*/
		b2BodyDef bodyDefinition;

		/** \brief Direct handle to b2Body of component. */
		b2Body* body;

		/** \brief Shape of b2Body.
		*
		* Only rectangles are supported currently.
		*/
		b2PolygonShape shape;

		/** \brief Properties of b2Body. */
		b2FixtureDef fixture;

		bool dynamic;

		/** \brief Has component been initialised by PhysicsSystem.
		*
		* \sa PhysicsSystem::Update 
		*/
		bool initialised;
	};
}

#endif