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
#include <scene\TextureCoordinates.h>

using namespace pm;
using namespace std;

SpriteBatch* SpriteBatch::instance = nullptr;

SpriteBatch* SpriteBatch::GetInstance()
{
	if (instance == nullptr)
	{
		instance = NEW SpriteBatch();
		CreateTextShader();
	}
	return instance;
}

void SpriteBatch::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}

void SpriteBatch::CreateTextShader()
{
	DEBUG_GL_ERROR_CLEAR();

	bool tempCheck = GetInstance()->textShader.AddShader("DEF_VERTEX_SHADER.txt", GL_VERTEX_SHADER); // Create default vertex shader.
	DEBUG_GL_ERROR();
	//ASSERT(tempCheck);

	tempCheck = GetInstance()->textShader.AddShader("DEF_TEXT_FRAGMENT_SHADER.txt", GL_FRAGMENT_SHADER); // Create default fragment shader.
	DEBUG_GL_ERROR();
	//ASSERT(tempCheck);

	GetInstance()->textShader.AddVertexAttribPointer("attrPosition", 3, 9, 0); // Vertex attributes defined by default shaders.
	GetInstance()->textShader.AddVertexAttribPointer("attrColor", 4, 9, 3);
	GetInstance()->textShader.AddVertexAttribPointer("texPosition", 2, 9, 7);
	
	GetInstance()->textShader.LinkProgram();
	GetInstance()->textShader.UseProgram();

	glEnable(GL_BLEND);
	DEBUG_GL_ERROR();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	DEBUG_GL_ERROR();

	glEnable(GL_DEPTH_TEST);
	glClearDepthf(1.0);

	glDepthFunc(GL_LEQUAL);
	DEBUG_GL_ERROR();

	GLint tempLocation = glGetUniformLocation(GetInstance()->textShader.GetShaderProgramLocation(), "image");
	DEBUG_GL_ERROR();

	glUniform1i(tempLocation, 0);
	DEBUG_GL_ERROR();

	DEBUG_INFO(("Text shaders done!"));
};

void SpriteBatch::Draw()
{
	// Prepare layers for drawing.
	BatchAllLayers();


	//static laýer nro 10
	for (unsigned int j = 0; j < opaqueLayerBatchVector[10].size(); j++)
	{
		RenderSystem::GetInstance()->Draw(&opaqueLayerBatchVector[10].at(j));
	}
	for (unsigned int j = 0; j < translucentLayerBatchVector[10].size(); j++)
	{
		RenderSystem::GetInstance()->Draw(&translucentLayerBatchVector[10].at(j));
	}
	//end static laýer nro 10

	// Draw all gameEntities on every ten layers. (0-9)
	for (unsigned int i = 0; i < 10; i++)
	{
		// Disable blend and set depthMask true for opaqueGameEntities.
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);

		for (unsigned int j = 0; j < textLayerBatchVector[i].size(); j++)
		{
			RenderSystem::GetInstance()->Draw(&textLayerBatchVector[i].at(j), &textShader);
		}

		for (unsigned int j = 0; j < opaqueLayerBatchVector[i].size(); j++)
		{
			RenderSystem::GetInstance()->Draw(&opaqueLayerBatchVector[i].at(j));
		}

		// Enable blend and set depthMask false for translucentGameEntities.
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);

		for (unsigned int j = 0; j < translucentLayerBatchVector[i].size(); j++)
		{
			RenderSystem::GetInstance()->Draw(&translucentLayerBatchVector[i].at(j));
		}

		// Clear gameEntities from current layer.
		opaqueLayerBatchVector[i].clear();
		translucentLayerBatchVector[i].clear();
		textLayerBatchVector[i].clear();
	}

	// Clear vectors for gameEntities added during draw cycle.
	opaqueGameEntityVector.clear();
	translucentGameEntityVector.clear();
	textEntityVector.clear();
}

void SpriteBatch::Draw(Shader* customShader)
{
	// Prepare layers for drawing.
	BatchAllLayers();


	//static laýer nro 10

	for (unsigned int j = 0; j < opaqueLayerBatchVector[10].size(); j++)
	{
		RenderSystem::GetInstance()->Draw(&opaqueLayerBatchVector[10].at(j), customShader);
	}
	for (unsigned int j = 0; j < translucentLayerBatchVector[10].size(); j++)
	{
		RenderSystem::GetInstance()->Draw(&translucentLayerBatchVector[10].at(j), customShader);
	}
	//end static laýer nro 10

	// Draw all gameEntities on every ten layers. (0-9)
	for (unsigned int i = 0; i < 10; i++)
	{
		// Disable blend and set depthMask true for opaqueGameEntities.
		// Alpha blending?
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);

		for (unsigned int j = 0; j < opaqueLayerBatchVector[i].size(); j++)
		{
			RenderSystem::GetInstance()->Draw(&opaqueLayerBatchVector[i].at(j), customShader);
		}

		// Enable blend and set depthMask false for translucentGameEntities.
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);

		for (unsigned int j = 0; j < translucentLayerBatchVector[i].size(); j++)
		{
			RenderSystem::GetInstance()->Draw(&translucentLayerBatchVector[i].at(j), customShader);
		}

		for (unsigned int j = 0; j < textLayerBatchVector[i].size(); j++)
		{
			RenderSystem::GetInstance()->Draw(&textLayerBatchVector[i].at(j), &textShader);
		}

		// Clear gameEntities from current layer.
		opaqueLayerBatchVector[i].clear();
		translucentLayerBatchVector[i].clear();
		textLayerBatchVector[i].clear();
	}
	// Clear vectors for gameEntities added during draw cycle.
	opaqueGameEntityVector.clear();
	translucentGameEntityVector.clear();
	textEntityVector.clear();
}


void SpriteBatch::AddGameEntity(GameEntity* entity, bool transparent)
{
	if (transparent)
		AddTranslucentGameEntity(entity);
	else
		AddOpaqueGameEntity(entity);
}

void SpriteBatch::AddStaticGameEntity(GameEntity* entity)
{
	if (entity->GetComponent<Texture>()->GetTranslucency() == Texture::TRANSLUCENT)
		Layers[10].translucentGO.push_back(entity);
	else
	{
		Layers[10].opaqueGO.push_back(entity);
	}
}

void SpriteBatch::AddGameEntity(GameEntity* entity)
{
	int test = entity->GetComponent<Texture>()->GetTranslucency();
	ASSERT_NEQUAL(entity->GetComponent<Texture>(),  nullptr);
	if (entity->GetComponent<Texture>()->GetTranslucency() == Texture::TRANSLUCENT)
		AddTranslucentGameEntity(entity);
	else if (entity->GetComponent<Texture>()->GetTranslucency() == Texture::OPAQUE)
		AddOpaqueGameEntity(entity);
}

void SpriteBatch::AddTranslucentGameEntity(GameEntity* gameEntity)
{
	translucentGameEntityVector.push_back(gameEntity);
}

void SpriteBatch::AddOpaqueGameEntity(GameEntity* gameEntity)
{
	opaqueGameEntityVector.push_back(gameEntity);
}

void SpriteBatch::AddOpaqueGameEntity(std::vector<GameEntity*> entityVector)
{
	for (unsigned int i = 0; i < entityVector.size(); i++)
		opaqueGameEntityVector.push_back(entityVector.at(i));
}

void SpriteBatch::AddText(Text* textEntity)
{
	for (unsigned int i = 0; i < textEntity->GetTextVector().size(); i++)
		textEntityVector.push_back(textEntity->GetTextVector().at(i));
}

SpriteBatch::SpriteBatch()
{
	// Shouldn't it be reserve instead of resize?
	Layers.resize(11);

	opaqueLayerBatchVector.resize(11);
	translucentLayerBatchVector.resize(11);
	textLayerBatchVector.resize(11);
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

void SpriteBatch::CreateLayers()
{
	// Store each gameEntity on a layer according to it's depth.

	for (unsigned int i = 0; i < opaqueGameEntityVector.size(); i++)
	{
		int depth = 9; // In case there is no transformable component.
		if (opaqueGameEntityVector[i]->GetComponent<Transformable>() != nullptr)
		{
			depth = opaqueGameEntityVector[i]->GetComponent<Transformable>()->GetDepth();
		}
		Layers[depth].opaqueGO.push_back(opaqueGameEntityVector[i]);
	}

	for (unsigned int i = 0; i < translucentGameEntityVector.size(); i++)
	{
		int depth = 9;
		if (translucentGameEntityVector[i]->GetComponent<Transformable>() != nullptr)
		{
			depth = translucentGameEntityVector[i]->GetComponent<Transformable>()->GetDepth();
		}
		Layers[depth].translucentGO.push_back(translucentGameEntityVector[i]);
	}

	for (unsigned int i = 0; i < textEntityVector.size(); i++)
	{
		int depth = 9;
		if (textEntityVector[i]->GetComponent<Transformable>() != nullptr)
		{
			depth = textEntityVector[i]->GetComponent<Transformable>()->GetDepth();
		}
		Layers[depth].textGO.push_back(textEntityVector[i]);
	}
}

void SpriteBatch::BatchLayerComponents(int layer, LAYERTYPE type)
{
	// Vectors to make code bit cleaner.
	std::vector<GameEntity*>* gameEntityVectorPointer;
	std::vector<Batch>* batchVectorPointer;

	// Select if batched GameEntities will be opaque or translucent.
	if (type == OPAQUE)
	{
		gameEntityVectorPointer = &Layers[layer].opaqueGO;
		batchVectorPointer = &opaqueLayerBatchVector[layer];
	}
	else if (type == TRANSLUCENT)
	{
		gameEntityVectorPointer = &Layers[layer].translucentGO;
		batchVectorPointer = &translucentLayerBatchVector[layer];
	}
	else if (type == TEXT)
	{
		gameEntityVectorPointer = &Layers[layer].textGO;
		batchVectorPointer = &textLayerBatchVector[layer];
	}

	// Less vectors to be called, cleaning a bit.
	std::vector<GameEntity*>& gameEntityVector = *gameEntityVectorPointer;
	std::vector<Batch>& batchVector = *batchVectorPointer;

	// Go throught all layers to find data to be used on current batch.
	for (unsigned int i = 0; i < gameEntityVector.size(); i++)
	{
		// Create temporary storages for data gathered from current gameEntity.
		std::vector<GLfloat> tempVertexData;
		std::vector<GLushort> tempIndexData;
		glm::mat4 tempTransformMatrix = glm::mat4();
		GLuint tempTextureIndex;

		// Creates new batch if there is no batch created yet for the texture.
		bool newBatch = true;

		if (IsDrawable(gameEntityVector[i]))
		{
			// Gather data to from current gameEntity to other parameters.
			ParseData(gameEntityVector[i], &tempVertexData, &tempIndexData, &tempTransformMatrix, &tempTextureIndex);

			for (unsigned k = 0; k < batchVector.size(); k++)
			{
				// If there is texture with same index as new one, add data to batch.
				if (batchVector[k].textureIndex == tempTextureIndex)
				{
					// Add found data to batch with same texture.
					batchVector[k].AddData(tempVertexData, tempIndexData, tempTransformMatrix);
					newBatch = false;
					break;
				}
			}
			// If no batches with same texture were found, create new batch and add found data to it.
			if (newBatch)
				batchVector.push_back(Batch(tempVertexData, tempIndexData, tempTransformMatrix, tempTextureIndex));
		}
	}
}

void SpriteBatch::BatchAllLayers()
{
	// Create layers for this batch.
	CreateLayers();

	for (unsigned int i = 0; i < Layers.size(); i++)
	{
		// Batch opaqueGO
		BatchLayerComponents(i, OPAQUE);
		// Batch TranslucentGO
		BatchLayerComponents(i, TRANSLUCENT);
		// Batch TextGO
		BatchLayerComponents(i, TEXT);
	}
	for (unsigned int i = 0; i < Layers.size() - 1; i++)//huom! (Layers.size() - 1) may cause problems
	{
		// Clear layers created in CreateLayers();
		Layers[i].opaqueGO.clear();
		Layers[i].translucentGO.clear();
		Layers[i].textGO.clear();
	}
}

void SpriteBatch::ParseData(GameEntity* gameEntity,
	std::vector<GLfloat>* vertexData,
	std::vector<GLushort>* indexData,
	glm::mat4* transformMatrix,
	GLuint* textureIndex)
{
	std::vector<GLfloat> vertexPos;
	int depth = 0;
	std::vector<GLfloat> vertexTexPos;
	glm::vec4 vertexColor;

	/// SHAPE ///
	if (gameEntity->GetComponent<Rectangle>() == nullptr)
	{
		// Should be edited back to shape class.
		DEBUG_WARNING(("GameEntity in SpriteBatch has no SHAPE."));
		return;
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
		DEBUG_WARNING(("Gathering data from GameEntity without TRANSFORMABLE."));
		*transformMatrix = glm::mat4(1);
	}
	else
	{
		*transformMatrix = gameEntity->GetComponent<Transformable>()->GetTransformMatrix(); // Do transform magic.
		depth = gameEntity->GetComponent<Transformable>()->GetDepth();
	}

	/// TEXTURE ///
	if (gameEntity->GetComponent<Texture>() == nullptr)
	{
		*textureIndex = -1;
		for (unsigned int i = 0; i < 8; i++)
			vertexTexPos.push_back(0);

		// DEBUG_WARNING(("Gathering data from GameEntity without TEXTURE."));
	}
	else
	{
		*textureIndex = gameEntity->GetComponent<Texture>()->GetId();

		if (gameEntity->GetComponent<TextureCoordinates>() == nullptr)
		{
			glm::fvec2 tempTextureSize = gameEntity->GetComponent<Texture>()->GetTextureSize();
			glm::fvec2 tempVec = gameEntity->GetComponent<Texture>()->GetTrueSize();

			vertexTexPos.push_back(0.0f);
			vertexTexPos.push_back(0.0f);

			vertexTexPos.push_back(0.0f);
			vertexTexPos.push_back((tempVec.y / tempTextureSize.y));

			vertexTexPos.push_back((tempVec.x / tempTextureSize.x));
			vertexTexPos.push_back(0.0f);

			vertexTexPos.push_back((tempVec.x / tempTextureSize.x));
			vertexTexPos.push_back((tempVec.y / tempTextureSize.y));
		}
		else
		{
			glm::uvec2 tempTextureSize = gameEntity->GetComponent<Texture>()->GetTextureSize();
			std::vector<GLfloat> tempVec = gameEntity->GetComponent<TextureCoordinates>()->GetTextureCoordinates();

			vertexTexPos.push_back(tempVec[0] / tempTextureSize.x);
			vertexTexPos.push_back((tempVec[3] / tempTextureSize.y));

			vertexTexPos.push_back(tempVec[0] / tempTextureSize.x);
			vertexTexPos.push_back((tempVec[1] / tempTextureSize.y));

			vertexTexPos.push_back(tempVec[2] / tempTextureSize.x);
			vertexTexPos.push_back((tempVec[3] / tempTextureSize.y));

			vertexTexPos.push_back(tempVec[2] / tempTextureSize.x);
			vertexTexPos.push_back((tempVec[1] / tempTextureSize.y));
		}
	}

	/// COLOR ///
	if (gameEntity->GetComponent<Color>() == nullptr)
	{
		vertexColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		vertexColor = gameEntity->GetComponent<Color>()->GetColor();
	}

	for (unsigned int i = 0; i < 4; i++)
	{
		vertexData->push_back(vertexPos[i * 2]);
		vertexData->push_back(vertexPos[i * 2 + 1]);
		vertexData->push_back(0);

		vertexData->push_back(vertexColor.x);
		vertexData->push_back(vertexColor.y);
		vertexData->push_back(vertexColor.z);
		vertexData->push_back(vertexColor.w);

		vertexData->push_back(vertexTexPos[i * 2]);
		vertexData->push_back(vertexTexPos[i * 2 + 1]);
	}
}