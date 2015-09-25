#ifndef HITBOX_H
#define HITBOX_H

#include <graphics\Rectangle.h>
#include <scene\CameraSystem.h>
#include <scene\Component.h>
#include <scene\GameEntity.h>

#include <glm\gtc\matrix_transform.hpp>
#include <glm\vec2.hpp>

#include <vector>

namespace pm
{
	class Hitbox : public Component
	{
	public:
		Hitbox(){};
		~Hitbox(){};
		bool CheckCollision(glm::vec2 touchCoordinates);
	};
}

#endif //HITBOX_H