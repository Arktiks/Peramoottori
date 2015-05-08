#ifndef TAILCOMPONENT_H
#define TAILCOMPONENT_H

#include <TailEntity.h>
#include <scene\Component.h>
#include <glm\vec2.hpp>
#include <vector>
using namespace pm;

class TailComponent : public Component
{
public:
	TailComponent(float fadeTime);
	~TailComponent();

	void PushPosition(glm::vec2 position);
	void Update(float time);
private:
	std::vector<TailEntity*> tail;
};

#endif