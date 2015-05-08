#ifndef TAILENTITY_H
#define TAILENTITY_H
#include "SpriteObject.h"
#include <glm\vec2.hpp>

class TailEntity : public SpriteObject
{
public:
	TailEntity(glm::vec2 position, float fadeTime, pm::Texture* texture);
	TailEntity(glm::vec2 position, float fadeTime);
	~TailEntity();
	bool Update(float time);
	bool CheckDestruction();
	float fadeTime;
	float currentFadeTime;
};
#endif

