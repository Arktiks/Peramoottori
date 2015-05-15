#include "Smoke.h"

Smoke::Smoke(pm::Texture* texture, glm::vec2 textureRectSize, std::vector<glm::vec2> texturePositionVector) :SpriteObject(texture)
{
	this->texturePositionVector = texturePositionVector;
	this->textureRectSize = textureRectSize;
	currentIndex = 0;
	UpdateTexturePosition();
	done = false;

}
Smoke::~Smoke()
{
}

void Smoke::Update(float deltaTime)
{

	timer += deltaTime;
	
	if (timer > 1000000)
	{
		UpdateTexturePosition();
		timer = 0;
	}
}

void Smoke::UpdateTexturePosition()
{
	
	if (currentIndex == texturePositionVector.size() - 1)
	{
		currentIndex = 0;
		done = true;
		return;
	}
	pm::Texture* texture = GetComponent<pm::Texture>();
	glm::vec2 leftTop(texturePositionVector[currentIndex].x, texturePositionVector[currentIndex].y);
	glm::vec2 rightBottom(texturePositionVector[currentIndex].x + textureRectSize.x,
		texturePositionVector[currentIndex].y + textureRectSize.y);
	texture->SetTextureVertices(leftTop, rightBottom);
	currentIndex++;
}