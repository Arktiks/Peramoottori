#include "Texture.h"

using namespace pm;
using namespace std;

void pm::Texture::SetTextureSize(glm::uvec2 textureSize)
{
	(this->textureSize.x) = textureSize.x;
	(this->textureSize.y) = textureSize.y;
	SetTextureVertices();
}

void pm::Texture::SetTextureVertices()
{
	SetTextureVertices(glm::vec2(0, 0), textureSize);
}

void pm::Texture::SetTextureVertices(glm::vec2 leftTop, glm::vec2 rightBottom)
{
	textureVertex.clear();

	textureVertex.push_back(leftTop.x / textureSize.x);
	textureVertex.push_back(1 - (leftTop.y / textureSize.y));

	textureVertex.push_back(leftTop.x / textureSize.x);
	textureVertex.push_back(1 - (rightBottom.y / textureSize.y));

	textureVertex.push_back(rightBottom.x / textureSize.x);
	textureVertex.push_back(1 - (leftTop.y / textureSize.y));

	textureVertex.push_back(rightBottom.x / textureSize.x);
	textureVertex.push_back(1 - (rightBottom.y / textureSize.y));
}