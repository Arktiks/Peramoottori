#ifndef HITBOX_H
#define HITBOX_H

#include <graphics\Rectangle.h>
#include <scene\CameraSystem.h>
#include <scene\Component.h>
#include <scene\GameEntity.h>

#include <glm\gtc\matrix_transform.hpp>
#include <glm\vec2.hpp>

#include <vector>

/** \internal Work in progress. */

namespace pm
{
	/** \brief Used to see if touch hits the GameEntity.
	* When added to a GameEntity, can be used to see if a touch is in the area of the GameEntity
	*/
	class Hitbox : public Component
	{
	public:
		/**
		* \brief Default constructor for Hitbox
		*/
		Hitbox(){};
		/**
		* \brief Default destructor for Hitbox
		*/
		~Hitbox(){};
		/** \brief Check collision with touchCoordinates
		* When called, returns collision confirmation with the touchCoordinates.
		* Automatically calculates the Camera inversion to the touchCoordinates.
		* \param[in] touchCoordinates TouchCoordinates from Input
		* \return bool (true / false) 
		*/
		bool CheckCollision(glm::vec2 touchCoordinates);
	};
}

#endif //HITBOX_H