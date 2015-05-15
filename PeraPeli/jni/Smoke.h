#pragma once
#include "SpriteObject.h"
#include <vector>
class Smoke:
	public SpriteObject
{
public:
	Smoke(pm::Texture* texture, glm::vec2 textureRectSize, std::vector<glm::vec2> texturePositionVector);
	~Smoke();

	void Update(float deltaTime);
	void UpdateTexturePosition();

private:

	int currentIndex;
	std::vector<glm::vec2> texturePositionVector;
	glm::vec2 textureRectSize;
	float timer;
};

