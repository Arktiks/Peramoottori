#include "SpriteBatch.h"
#include "Drawable.h"
#include "Color.h"
#include "Shape.h"
#include "TextureRectangle.h"
#include "Texture.h"
#include "scene\Transformable.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\transform.hpp"
#include <algorithm>
#include <core\Passert.h>
#include <core\Log.h>
#include <core\Memory.h>


using namespace pm;


SpriteBatch* SpriteBatch::instance = nullptr;

SpriteBatch::SpriteBatch()
{

}

SpriteBatch* SpriteBatch::GetInstance()
{
	if (instance == nullptr)
	{
		instance = NEW SpriteBatch();
	}
	return instance;
}

void SpriteBatch::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}

void SpriteBatch::AddGameEntityToVector(GameEntity *gameEntity)
{
	gameEntityVector.push_back(gameEntity);
}

bool SpriteBatch::CheckIfDrawable(GameEntity *gameEntity)
{
	if (gameEntity->GetComponent<Drawable>() == nullptr)
		return false;
	else
		return gameEntity->GetComponent<Drawable>()->GetDrawState();
}

Sprite GatherDataFromComponents(GameEntity *gameEntity)
{
	Sprite sprite;
	glm::mat4 translationMatrix;
	std::vector<GLfloat> vertexPos;
	GLfloat depth;
	glm::vec4 vertexTexPos;
	glm::vec4 vertexColor;
	std::vector<GLuint> indices;
	if (gameEntity->GetComponent<Shape>() == nullptr)
	{
		//NO SHAPE
	}
	else
	{
		vertexPos = gameEntity->GetComponent<Shape>()->GetVertices();
		indices = gameEntity->GetComponent<Shape>()->GetIndices();
	}

	if (gameEntity->GetComponent<Transformable>() == nullptr)
	{
		translationMatrix = glm::mat4();
	}
	else
	{
		Transformable* transform = gameEntity->GetComponent<Transformable>();

		translationMatrix = glm::translate(glm::vec3(transform->GetPosition(), 0.0f));
		translationMatrix *= glm::rotate(transform->GetRotation(), glm::vec3(0, 0, 1));
		translationMatrix *= glm::scale(glm::vec3(transform->GetScale(), 0.0f));
		depth = transform->GetDepth();
	}

	if (gameEntity->GetComponent<TextureRectangle>() == nullptr)
	{
		vertexTexPos = glm::vec4(0, 1, 1, 0);
	}
	else
	{
		vertexTexPos = GetComponent<TextureRectangle>()->GetTextureRectangle();
	}

	if (gameEntity->GetComponent<Color>() == nullptr)
	{
		//NO COLOR
		vertexColor = glm::vec4(255, 50, 150, 1);
	}
	else
	{
		vertexColor = gameEntity->GetComponent<Color>()->GetColor();
	}

	// TEXTURECOMPONENT WIP
	std::vector<GLfloat> vertexData;
	return sprite;
}

void SpriteBatch::AddSpriteToBatch(Sprite sprite)
{
	for (unsigned i = 0; i < batchVector.size(); i++)
	{
			// If there is a texture with same index as new one, add data to batch.
		if (batchVector[i].textureIndex == sprite.GetTextureIndex());
		{
			batchVector[i].AddData(sprite.GetVertexData(), sprite.GetIndexData(), sprite.GetTransformMatrix());
			return;
		}
	}
			// If no batches with same texture were found, create new batch and add data to it.
	Batch newBatch(sprite.GetVertexData(), sprite.GetIndexData(), sprite.GetTransformMatrix(), sprite.GetTextureIndex());
	batchVector.push_back(newBatch);
}

std::vector<GLfloat> SpriteBatch::CreateVertexData(std::vector<GLfloat> vertexPos
	GLfloat depth, glm::vec4 vertexTexPos, glm::vec4 vertexColor)
{
	std::vector<GLfloat> vertexData;
	for (int i = 0; i < 4; i++)
	{
		vertexData.push_back(vertexPos[i * 2]);
		vertexData.push_back(vertexPos[i * 2 + 1]);
		vertexData.push_back(depth);

		vertexData.push_back(vertexColor.x);
		vertexData.push_back(vertexColor.y);
		vertexData.push_back(vertexColor.z);

		vertexData.push_back(vertexTexPos[]);
		vertexData.push_back(vertexTexPos[])
	}
}