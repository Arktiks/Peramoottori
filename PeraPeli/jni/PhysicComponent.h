#ifndef PHYSICCOMPONENT_H
#define PHYSICCOMPONENT_H
#include <scene\Component.h>
#include <glm\vec2.hpp>
using namespace pm;

class PhysicComponent : public Component
{
public:
	PhysicComponent();
	~PhysicComponent();

	void SetVelocity(glm::vec2 newVelocity);
	void SetPosition(glm::vec2 newPosition);
	glm::vec2 GetVelocity();
	glm::vec2 GetPosition();
private:
	glm::vec2 velocity;
	glm::vec2 position;
};

#endif