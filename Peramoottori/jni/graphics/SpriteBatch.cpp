#include "SpriteBatch.h"
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
	// TODO: Check if sprite will be drawn, using components.
}

Sprite GatherDataFromComponents(GameEntity *gameEntity)
{
	// Gather stuff for the sprite using components. Sprite will be batched and forwarded to RenderSystem
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
