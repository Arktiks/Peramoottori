#ifndef HITBOX_H
#define HITBOX_H

#include <scene\Component.h>
#include <glm\vec2.hpp>

namespace pm
{

	/** \brief Used to see if touch hits the GameEntity.
	*
	* When added to GameEntity, can be used to see if a touch is in the area of the GameEntity
	*
	* \ingroup Scene
	*/
	class Hitbox : public Component
	{
	public:
		
		/**
		* \brief Default constructor.
		*/
		Hitbox(){};
		
		/**
		* \brief Default destructor
		*/
		~Hitbox(){};

		/** \brief Check collision with touchCoordinates.
		*
		* Automatically calculates camera inversion to the touchCoordinates.
		*
		* \param[in] touchCoordinates Coordinates from Input.
		* \return true if GameEntity contains touchCoordinates.
		*/
		bool CheckCollision(glm::vec2 touchCoordinates);
	};
}

#endif //HITBOX_H