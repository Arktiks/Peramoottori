#include "SpriteBatch.h"

#include <core\Passert.h>
#include <core\Log.h>
#include <core\Memory.h>

#include "RenderSystem.h"
#include "Drawable.h"
#include "Color.h"
#include "Rectangle.h"

#include <scene\Texture.h>
#include <scene\Transformable.h>

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

using namespace pm;
using namespace std;

SpriteBatch* SpriteBatch::instance = nullptr;

SpriteBatch* SpriteBatch::GetInstance()
{
	if (instance == nullptr)
		instance = NEW SpriteBatch();
	return instance;
}

void SpriteBatch::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}

void SpriteBatch::Draw()
{
	BatchComponents();

	for (int i = 0; i < batchVector.size(); i++)
		RenderSystem::GetInstance()->Draw(&batchVector[i]);

	gameEntityVector.clear();
	opaqueGameEntityVector.clear();
	batchVector.clear();
}

void SpriteBatch::AddGameEntity(GameEntity* gameEntity)
{
	gameEntityVector.push_back(gameEntity);
}

void SpriteBatch::AddOpaqueGameEntity(GameEntity* gameEntity)
{
	opaqueGameEntityVector.push_back(gameEntity); 
}

void SpriteBatch::AddText(Text* textEntity)
{
	for (int i = 0; i < textEntity->GetTextVector().size(); i++)
		opaqueGameEntityVector.push_back(textEntity->GetTextVector().at(i));
}

bool SpriteBatch::IsDrawable(GameEntity* gameEntity)
{
	if (gameEntity->GetComponent<Drawable>() == nullptr)
		return false;
	else if (gameEntity->GetComponent<Rectangle>() == nullptr)
		return false;
	else
		return gameEntity->GetComponent<Drawable>()->GetDrawState();
}

void SpriteBatch::BatchComponents()
{
	for (int i = 0; i < gameEntityVector.size(); i++)
	{
		std::vector<GLfloat> tempVertexData;
		std::vector<GLushort> tempIndexData;
		glm::mat4 tempTransformMatrix = glm::mat4();
		GLuint tempTextureIndex;
		bool newBatch = true;

		if (IsDrawable(gameEntityVector[i]))
		{
			ParseData(gameEntityVector[i], &tempVertexData, &tempIndexData, &tempTransformMatrix, &tempTextureIndex);

			for (unsigned k = 0; k < batchVector.size(); k++)
			{
				// If there is texture with same index as new one, add data to batch.
				if (batchVector[k].textureIndex == tempTextureIndex)
				{
					batchVector[k].AddData(tempVertexData, tempIndexData, tempTransformMatrix);
					newBatch = false;
					break;
				}
			}
			// If no batches with same texture were found, create new batch and add data to it.
			if (newBatch)
				batchVector.push_back(Batch(tempVertexData, tempIndexData, tempTransformMatrix, tempTextureIndex));
		}
	}

	// Somebody has to make this good.
	for (int i = 0; i < opaqueGameEntityVector.size(); i++)
	{
		std::vector<GLfloat> tempVertexData;
		std::vector<GLushort> tempIndexData;
		glm::mat4 tempTransformMatrix = glm::mat4();
		GLuint tempTextureIndex;
		bool newBatch = true;

		if (IsDrawable(opaqueGameEntityVector[i]))
		{
			ParseData(opaqueGameEntityVector[i], &tempVertexData, &tempIndexData, &tempTransformMatrix, &tempTextureIndex);

			for (unsigned k = 0; k < batchVector.size(); k++)
			{
				// If there is texture with same index as new one, add data to batch.
				if (batchVector[k].textureIndex == tempTextureIndex)
				{
					batchVector[k].AddData(tempVertexData, tempIndexData, tempTransformMatrix);
					newBatch = false;
					break;
				}
			}
			// If no batches with same texture were found, create new batch and add data to it.
			if (newBatch)
				batchVector.push_back(Batch(tempVertexData, tempIndexData, tempTransformMatrix, tempTextureIndex));
		}
	}
}

void SpriteBatch::ParseData(GameEntity* gameEntity,
	std::vector<GLfloat>* vertexData,
	std::vector<GLushort>* indexData,
	glm::mat4* transformMatrix,
	GLuint* textureIndex)
{
	std::vector<GLfloat> vertexPos;
	GLfloat depth = 0;
	std::vector<GLfloat> vertexTexPos;
	glm::vec4 vertexColor;

	/// SHAPE ///
	if (gameEntity->GetComponent<Rectangle>() == nullptr)
	{
		// Should be edited back to shape class.
		//DEBUG_WARNING(("Gathering data from GameEntity without SHAPE."));
	}
	else
	{
		vertexPos = gameEntity->GetComponent<Rectangle>()->GetVertices();
		*indexData = gameEntity->GetComponent<Rectangle>()->GetIndices();
		//ASSERT(vertexPos.empty());
		//ASSERT(indices.empty());
	}

	/// TRANSFORMABLE ///
	if (gameEntity->GetComponent<Transformable>() == nullptr)
	{
		//DEBUG_WARNING(("Gathering data from GameEntity without TRANSFORMABLE."));
	}
	else
	{
		Transformable* transform = gameEntity->GetComponent<Transformable>(); // Do transform magic.
		glm::mat4 tempMat = glm::mat4();
		tempMat = glm::scale(glm::vec3(transform->GetScale(), 0.0f)) * tempMat;
		tempMat = glm::rotate(transform->GetRotation()*3.14f / 180.0f, glm::vec3(0, 0, 1)) * tempMat;
		tempMat = glm::translate(glm::vec3(transform->GetPosition(), 0.0f)) * tempMat;
		*transformMatrix = tempMat;
		depth = transform->GetDepth();
	}

	/// TEXTURE ///
	if (gameEntity->GetComponent<Texture>() == nullptr)
	{
		*textureIndex = -1;
		for (int i = 0; i < 8; i++)
			vertexTexPos.push_back(0);

		//DEBUG_WARNING(("Gathering data from GameEntity without TEXTURE."));
	}
	else
	{
		vertexTexPos = gameEntity->GetComponent<Texture>()->GetTextureVertices();
		*textureIndex = gameEntity->GetComponent<Texture>()->GetId();
	}

	/// COLOR ///
	if (gameEntity->GetComponent<Color>() == nullptr)
	{
		vertexColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		vertexColor = gameEntity->GetComponent<Color>()->GetColor();
	}

	for (int i = 0; i < 4; i++)
	{
		vertexData->push_back(vertexPos[i * 2]);
		vertexData->push_back(vertexPos[i * 2 + 1]);
		vertexData->push_back(depth);
				  
		vertexData->push_back(vertexColor.x);
		vertexData->push_back(vertexColor.y);
		vertexData->push_back(vertexColor.z);
		vertexData->push_back(vertexColor.w);
				  
		vertexData->push_back(vertexTexPos[i * 2]);
		vertexData->push_back(vertexTexPos[i * 2 + 1]);
	}
}