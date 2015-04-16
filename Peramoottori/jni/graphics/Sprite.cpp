#include "Sprite.h"
#include <core\Log.h>
#include <core\Passert.h>

using namespace pm;

Sprite::Sprite(std::vector<GLfloat> vertexData, std::vector<GLushort> indexData,
	glm::mat4 transformMatrix,
	GLuint textureIndex)
{
	(this->vertexData) = vertexData;
	(this->indexData) = indexData;
	(this->transformMatrix) = transformMatrix;
	(this->textureIndex) = textureIndex;

	ASSERT(ValidateData()); // Will be removed on release.
}

void Sprite::SetData(std::vector<GLfloat> vertexData, std::vector<GLushort> indexData,
	glm::mat4 transformMatrix,
	GLuint textureIndex)
{
	(this->vertexData) = vertexData;
	(this->indexData) = indexData;
	(this->transformMatrix) = transformMatrix;
	(this->textureIndex) = textureIndex;

	ASSERT(ValidateData());
}

bool Sprite::ValidateData()
{
	if (vertexData.empty())
	{
		DEBUG_WARNING(("Sprite has no VERTEX_DATA."));
		return false;
	}
	else if (indexData.empty())
	{
		DEBUG_WARNING(("Sprite has no INDEX_DATA."));
		return false;
	}
	else if (textureIndex < 0)
	{
		DEBUG_WARNING(("Sprite TEXTURE_INDEX is faulty."));
		return false;
	}
	else
		return true;
}