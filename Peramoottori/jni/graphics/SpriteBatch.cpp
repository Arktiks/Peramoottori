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
	if (gameEntity->GetComponent<Shape>() == nullptr)
	{
		//NO SHAPE
	}
	else
	{

	}

	if (gameEntity->GetComponent<Transformable>() == nullptr)
	{
		// NO TRANSFORMCOMPONENT
	}
	else
	{
		//gameEntity->GetComponent<Transformable>()->
	}

	if (gameEntity->GetComponent<TextureRectangle>() == nullptr)
	{
		//NO TEXTURERECTANGLE
	}
	else
	{

	}

	if (gameEntity->GetComponent<Color>() == nullptr)
	{
		//NO COLOR
	}
	else
	{

	}

	// TEXTURECOMPONENT WIP

	return sprite;
}

void SpriteBatch::AddSpriteToBatch(Sprite sprite)
{
	for (unsigned i = 0; i < batchVector.size(); i++)
	{
			// If there is a texture with same index as new one, add data to batch.
		if (batchVector[i].textureIndex == sprite.textureIndex);
		{
			batchVector[i].AddData(sprite.vertexData, sprite.indexData, sprite.transformMatrix);
			return;
		}
	}
			// If no batches with same texture were found, create new batch and add data to it.
	Batch newBatch(sprite.vertexData, sprite.indexData, sprite.transformMatrix, sprite.textureIndex);
	batchVector.push_back(newBatch);
}
