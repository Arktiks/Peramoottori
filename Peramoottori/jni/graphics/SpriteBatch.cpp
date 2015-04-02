#include "SpriteBatch.h"
#include <algorithm>
#include <core\Passert.h>
#include <core\Log.h>
#include <core\Memory.h>

using namespace pm;

// TODO: GameObjectin tarkastus, joku muu hoitaa?

SpriteBatch* SpriteBatch::instance = nullptr;

SpriteBatch::SpriteBatch()
{
	screenSize = glm::vec2(1200, 720); // Temporary, wont be needed in future
	spriteAmount = 0;

}

SpriteBatch* SpriteBatch::GetInstance()
{
	if (instance == nullptr)
	{
		instance = NEW SpriteBatch();
	}
	return instance;
}

// Renderöijä täytyy alustaa vasta kun konteksti on valmis (Kutsutaan siten applicationin puolelta).

void SpriteBatch::Initialize()
{
	glEnable(GL_TEXTURE_2D);
	glGenBuffers(2, &buffer[0]);
	CreateShaders();
	DEBUG_INFO(("SpriteBatch initialize finished."));
}

// Hoidetaan renderöijällä kai? Ainakin jossakin muuaalla kuin täällä.
void SpriteBatch::CreateShaders()
{
	bool tempCheck = false;

	tempCheck = defaultShader.AddShader("TestVertexShader.txt", GL_VERTEX_SHADER);
	ASSERT(tempCheck);

	tempCheck = defaultShader.AddShader("TestFragmentShader.txt", GL_FRAGMENT_SHADER);
	ASSERT(tempCheck);

	defaultShader.AddVertexAttribPointer("attrPosition", 2, 7, 0);
	defaultShader.AddVertexAttribPointer("attrColor", 3, 7, 2);
	defaultShader.AddVertexAttribPointer("texPosition", 2, 7, 5);
	defaultShader.AddSamplerLocation("image");
	defaultShader.LinkProgram();

	DEBUG_INFO(("Shaders done!."));
}


void SpriteBatch::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}

void SpriteBatch::addSprite(std::vector<GLfloat> vertexData, std::vector<GLuint> indexData,
	glm::mat4 transformMatrix, GLuint textureIndex)
{
	for (unsigned i = 0; i < batchVector.size(); i++)
	{
			// If there is a texture with same index as new one, add data to batch.
		if (batchVector[i].textureIndex == textureIndex);
		{
			batchVector[i].AddData(vertexData, indexData, transformMatrix);
			return;
		}
	}
			// If no batches with same texture were found, create new batch and add data to it.
	Batch newBatch(vertexData, indexData, transformMatrix, textureIndex);
	batchVector.push_back(newBatch);
}

void SpriteBatch::Draw()
{
	Update();
	if (defaultShader.GetLinkStatus())
	{
		defaultShader.RunProgram();
	}

	// Tästä saadaan irti lajittelu, siirretään piirtofunktiot renderöinnille.
	if (sprites.size() != 0)
	{
		GLuint currentAtlasIndex = sprites[0]->texture.getId();
		
		unsigned totalIndiceAmount = 0;
		unsigned indiceAmount = 0;

		if (sprites[0]->draw)
		{
			indiceAmount = sprites[0]->indices.size();
		}

		for (unsigned i = 0; i < sprites.size(); i++)
		{
			if (i+1 == sprites.size())
			{
				glActiveTexture(GL_TEXTURE0);
				glEnable(GL_TEXTURE_2D);

				glUniform1i(defaultShader.samplerLoc, 0);
				glBindTexture(GL_TEXTURE_2D, currentAtlasIndex);

				glDrawElements(GL_TRIANGLES, indiceAmount, GL_UNSIGNED_INT,
					reinterpret_cast<GLvoid*>(totalIndiceAmount * sizeof(GLuint)));
				glBindTexture(GL_TEXTURE_2D, 0u);
			}

			else if (sprites[i + 1]->texture.getId() == currentAtlasIndex)
			{
				// Only add indices if sprite has draw = true
				// CreateBufferData()
				if (sprites[i + 1]->draw)
				{
					indiceAmount += sprites[i + 1]->indices.size();
				}
			}

			else
			{
				//draw sprites with last texture, set new texture and current indiceAmount to totalIndices.
				glActiveTexture(GL_TEXTURE0);
				glEnable(GL_TEXTURE_2D);

				glUniform1i(defaultShader.samplerLoc, 0);
				glBindTexture(GL_TEXTURE_2D, currentAtlasIndex);

				glDrawElements(GL_TRIANGLES, indiceAmount, GL_UNSIGNED_INT,
					reinterpret_cast<GLvoid*>(totalIndiceAmount * sizeof(GLuint)));
				glBindTexture(GL_TEXTURE_2D, 0u);

				totalIndiceAmount += indiceAmount;		//not needed
				indiceAmount = sprites[i + 1]->indices.size();
				currentAtlasIndex = sprites[i + 1]->texture.getId();
			}
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0u);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	}
}

void SpriteBatch::Update()
{
	// Bufferidatan luonti hoidetaan renderöijällä
	CreateBufferData();
	if (spriteAmount != sprites.size())
	{
		spriteAmount = sprites.size();
		BindBuffers();
	}

	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0u, vertexData.size()*sizeof(GLfloat), &vertexData[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
}

/// SpriteVector depth sort
/**
	Sorts sprites according to their draw depth.
*/



// Siirretään renderöinnille
void SpriteBatch::BindBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size()*sizeof(GLfloat), &vertexData.front(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size()*sizeof(GLuint), &indexData.front(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
}


// indexDatat ja vertexDatat luodaan täällä. Tarvitaan uusi sort, mikä lajittelee datan tekstuurin mukaan.
void SpriteBatch::CreateBufferData()
{
	indexData.clear();
	vertexData.clear();

	// add current vector to indexData, sort should have been called before this.
	for (unsigned i = 0; i < sprites.size(); i++)
	{
		if (sprites[i]->draw)
		{

			indexData.push_back(sprites[i]->indices[0] + i * 4);
			indexData.push_back(sprites[i]->indices[1] + i * 4);
			indexData.push_back(sprites[i]->indices[2] + i * 4);
			indexData.push_back(sprites[i]->indices[3] + i * 4);
			indexData.push_back(sprites[i]->indices[4] + i * 4);
			indexData.push_back(sprites[i]->indices[5] + i * 4);

			std::vector<GLfloat> tempVertices = createGLCoord(sprites[i]->vertices, sprites[i]->texture.getTextureSize());
			
			vertexData.insert(vertexData.end(), tempVertices.begin(), tempVertices.end());
		}
	}
}
// Tässä tehdään tarvittavat muunnokset yhden spriten verteksidataan, ja koostetaan yhteen.
std::vector<GLfloat> SpriteBatch::createGLCoord(std::vector<GLfloat> convertVertices, glm::vec2 textureSize)
{	
	std::vector<GLfloat> glVertexData;

	glVertexData.clear();
	for (int i = 0; i < 4; i++)
	{
		glm::vec2 position = PositionToGLCoord(glm::vec2(convertVertices[0 + i * 7], convertVertices[1 + i * 7]));
		glm::vec3 color = glm::vec3(convertVertices[2 + i * 7], convertVertices[3 + i * 7], convertVertices[4 + i * 7]);

		glVertexData.push_back(position.x);
		glVertexData.push_back(position.y);
		
		glVertexData.push_back(color.r);
		glVertexData.push_back(color.b);
		glVertexData.push_back(color.g);
		glVertexData.push_back(convertVertices[5 + i * 7]);
		glVertexData.push_back(convertVertices[6 + i * 7]);
	}

	return glVertexData;
}
// Ei tarvita
glm::vec2 SpriteBatch::PositionToGLCoord(glm::vec2 position)
{
	glm::vec2 tempPosCoord;
	tempPosCoord.x = 2 * (position.x / screenSize.x) - 1;
	tempPosCoord.y = 2 * (position.y / screenSize.y) - 1;
	return tempPosCoord;
}

// Ei tarvita
glm::vec2 SpriteBatch::TextureToGLCoord(glm::vec2 position, glm::vec2 spriteSize)
{
	glm::vec2 tempTexCoord;
	tempTexCoord.x = position.x / spriteSize.x;
	tempTexCoord.y = position.y / spriteSize.y;
	return tempTexCoord;
}

// Todennäköisesti muuttuvat:
/*void TempCreateShader()
{
}*/