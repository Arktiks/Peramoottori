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

	// Clean up SpriteBatch.
}

void SpriteBatch::Draw()
{
	for (int i = 0; i < gameEntityVector.size(); i++)
	{
		if (IsDrawable(gameEntityVector[i]))
		{
			Sprite sprite = GatherDataFromComponents(gameEntityVector[i]);
			AddSpriteToBatch(sprite);
		}
	}

	for (int i = 0; i < batchVector.size(); i++)
		RenderSystem::GetInstance()->Draw(batchVector[i]);

	gameEntityVector.clear();
	batchVector.clear();
}

void SpriteBatch::AddGameEntity(GameEntity* gameEntity)
{
	gameEntityVector.push_back(gameEntity);
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

Sprite SpriteBatch::GatherDataFromComponents(GameEntity* gameEntity)
{
	glm::mat4 translationMatrix = glm::mat4();
	glm::vec4 vertexColor;
	GLfloat depth = 0;
	GLuint textureID;

	std::vector<GLfloat> vertexPos;
	std::vector<GLfloat> vertexTexPos;
	std::vector<GLushort> indices;


	/// SHAPE ///
	if (gameEntity->GetComponent<Rectangle>() == nullptr)
	{
		// Should be edited back to shape class.
		DEBUG_WARNING(("Gathering data from GameEntity without SHAPE."));
	}
	else
	{
		vertexPos = gameEntity->GetComponent<Rectangle>()->GetVertices();
		indices = gameEntity->GetComponent<Rectangle>()->GetIndices();

		//ASSERT(vertexPos.empty());
		//ASSERT(indices.empty());
	}


	/// TRANSFORMABLE ///
	if (gameEntity->GetComponent<Transformable>() == nullptr)
	{
		DEBUG_WARNING(("Gathering data from GameEntity without TRANSFORMABLE."));
	}
	else
	{
		// Do transform magic.
		Transformable* transform = gameEntity->GetComponent<Transformable>();

		translationMatrix = glm::scale(glm::vec3(transform->GetScale(), 0.0f)) * translationMatrix;
		translationMatrix = glm::rotate(transform->GetRotation()*3.14f/180.0f, glm::vec3(0, 0, 1)) * translationMatrix;
		translationMatrix = glm::translate(glm::vec3(transform->GetPosition(), 0.0f)) * translationMatrix;
		
		depth = transform->GetDepth();
	}


	/// TEXTURE ///
	if (gameEntity->GetComponent<Texture>() == nullptr)
	{
		textureID = -1;
		for (int i = 0; i < 8; i++)
			vertexTexPos.push_back(0);

		DEBUG_WARNING(("Gathering data from GameEntity without TEXTURE."));
	}
	else
	{
		vertexTexPos = gameEntity->GetComponent<Texture>()->GetTextureVertices();
		textureID = gameEntity->GetComponent<Texture>()->GetId();
	}
	

	/// COLOR ///
	if (gameEntity->GetComponent<Color>() == nullptr)
	{
		vertexColor = glm::vec4(0.65f, 0.65f, 0.65f, 1.0f);
	} 
	else
		vertexColor = gameEntity->GetComponent<Color>()->GetColor();


	/// FINALIZE ///
	std::vector<GLfloat> vertexData;
	vertexData = CreateVertexData(vertexPos, depth, vertexTexPos, vertexColor);
	Sprite sprite(vertexData, indices, translationMatrix, textureID);

	return sprite;
}

void SpriteBatch::AddSpriteToBatch(Sprite sprite)
{
	for (unsigned i = 0; i < batchVector.size(); i++)
	{
		// If there is texture with same index as new one, add data to batch.
		if (batchVector[i].textureIndex == sprite.GetTextureIndex())
		{
			batchVector[i].AddData(sprite.GetVertexData(), sprite.GetIndexData(), sprite.GetTransformMatrix());
			return;
		}
	}

	// If no batches with same texture were found, create new batch and add data to it.
	Batch newBatch(sprite.GetVertexData(), sprite.GetIndexData(), sprite.GetTransformMatrix(), sprite.GetTextureIndex());
	batchVector.push_back(newBatch);
}

vector<GLfloat> SpriteBatch::CreateVertexData(vector<GLfloat> vertexPos,
	GLfloat depth,
	vector<GLfloat> vertexTexPos,
	glm::vec4 vertexColor)
{
	vector<GLfloat> vertexData;
	for (int i = 0; i < 4; i++)
	{
		vertexData.push_back(vertexPos[i * 2]);
		vertexData.push_back(vertexPos[i * 2 + 1]);
		vertexData.push_back(depth);

		vertexData.push_back(vertexColor.x);
		vertexData.push_back(vertexColor.y);
		vertexData.push_back(vertexColor.z);

		vertexData.push_back(vertexTexPos[i * 2]);
		vertexData.push_back(vertexTexPos[i * 2 + 1]);
	}

	return vertexData;
}