#include "SpriteBatch.h"
#include <algorithm>
#include <core\Passert.h>
#include <core\Log.h>

using namespace pm;

// TODO: Tuki indeksimäärältään erikokoisille spriteille tehdään piirtämällä kolmioita vain.
// Spritebatcheja on vain yksi, singleton? 
// Tämän kautta piirretään kaikki
SpriteBatch* SpriteBatch::instance = nullptr;

SpriteBatch::SpriteBatch()
{
	screenSize = glm::vec2(500, 500); // !!!!! Get real screen resolution!
	spriteAmount = 0;
	glGenBuffers(2, &buffer[0]);
}

SpriteBatch* SpriteBatch::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new SpriteBatch();
	}
	return instance;
}

void SpriteBatch::Initialize()
{
	bool tempCheck = false;
	
	tempCheck = defaultShader.AddShader("TestVertexShader.txt", GL_VERTEX_SHADER);
	ASSERT(tempCheck);

	tempCheck = defaultShader.AddShader("TestFragmentShader.txt", GL_FRAGMENT_SHADER);
	ASSERT(tempCheck);

	defaultShader.AddVertexAttribPointer("attrPosition", 2, 7, 0);
	defaultShader.AddVertexAttribPointer("attrColor", 3, 7, 2);
	defaultShader.AddVertexAttribPointer("textPosition", 2, 7, 5);

	defaultShader.LinkProgram();
	
	DEBUG_INFO(("SpriteBatch initialize finished."));
}

void SpriteBatch::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}

void SpriteBatch::addSprite(Sprite *sprite)
{
	sprites.push_back(sprite);
}

void SpriteBatch::Draw()
{
	Update();
	if (defaultShader.GetLinkStatus())
	{
		defaultShader.RunProgram();
	}

	// Draws textures that are in same layer. TODO: Add texture-sort to sort-function
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
				glBindTexture(GL_TEXTURE_2D, currentAtlasIndex);
				glDrawElements(GL_TRIANGLES, indiceAmount, GL_UNSIGNED_INT,
					reinterpret_cast<GLvoid*>(totalIndiceAmount * sizeof(GLuint)));
				glBindTexture(GL_TEXTURE_2D, 0u);
				break;
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
				glBindTexture(GL_TEXTURE_2D, currentAtlasIndex);
				glDrawElements(GL_TRIANGLES, indiceAmount, GL_UNSIGNED_INT,
					reinterpret_cast<GLvoid*>(totalIndiceAmount *sizeof(GLuint)));
				glBindTexture(GL_TEXTURE_2D, 0u);

				totalIndiceAmount += indiceAmount;		//not needed
				indiceAmount = sprites[i+1]->indices.size();
				currentAtlasIndex = sprites[i + 1]->texture.getId();
			}
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0u);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	}
}

void SpriteBatch::Update()
{
	CreateBufferData();
	if (spriteAmount != sprites.size())
	{
		spriteAmount = sprites.size();
		BindBuffers();
	}

	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0u, vertexData.size()*sizeof(GLfloat), &vertexData.front());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
}

/// SpriteVector depth sort
/**
	Sorts sprites according to their draw depth.
*/

void SpriteBatch::Sort()
{
	for (std::vector<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++)
	{
		std::sort(sprites.begin(), sprites.end(),
			[](Sprite* a, Sprite* b ){return (a->drawDepht > b->drawDepht); });
	}
}

void SpriteBatch::BindBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size()*sizeof(GLfloat), &vertexData.front(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0u);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size()*sizeof(GLuint), &indexData.front(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
}

void SpriteBatch::CreateBufferData()
{
	indexData.clear();
	vertexData.clear();

	// add current vector to indexData, sort should have been called before this.
	for (unsigned i = 0; i < sprites.size(); i++)
	{
		if (sprites[i]->draw)
		{

			indexData.push_back(sprites[i]->indices[0] + i * 6);
			indexData.push_back(sprites[i]->indices[1] + i * 6);
			indexData.push_back(sprites[i]->indices[2] + i * 6);
			indexData.push_back(sprites[i]->indices[3] + i * 6);
			indexData.push_back(sprites[i]->indices[4] + i * 6);
			indexData.push_back(sprites[i]->indices[5] + i * 6);

			std::vector<GLfloat> tempVertices = createGLCoord(sprites[i]->vertices, sprites[i]->texture.getTextureSize());
			
			vertexData.insert(vertexData.end(), tempVertices.begin(), tempVertices.end());
		}
	}
}

std::vector<GLfloat> SpriteBatch::createGLCoord(std::vector<GLfloat> convertVertices, glm::vec2 textureSize)
{	
	std::vector<GLfloat> glVertexData;

	glVertexData.clear();
	for (int i = 0; i < 4; i++)
	{
		glm::vec2 position = PositionToGLCoord(glm::vec2(convertVertices[0 + i * 7], convertVertices[1 + i * 7]));
		glm::vec3 color = ColorToGLCoord(glm::vec3(convertVertices[2 + i * 7], convertVertices[3 + i * 7], convertVertices[4 + i * 7]));
		//glm::vec2 texturePosition = TextureToGLCoord(glm::vec2(convertVertices[5 + i * 7], convertVertices[6 + i * 7]), textureSize);

		glVertexData.push_back(position.x);
		glVertexData.push_back(position.y);
		glVertexData.push_back(color.r);
		glVertexData.push_back(color.b);
		glVertexData.push_back(color.g);
		glVertexData.push_back(convertVertices[5+i*7]);
		glVertexData.push_back(convertVertices[6+i*7]);
	}

	return glVertexData;
}

glm::vec2 SpriteBatch::PositionToGLCoord(glm::vec2 position)
{
	glm::vec2 tempPosCoord;
	tempPosCoord.x = 2 * (position.x / screenSize.x) - 1;
	tempPosCoord.y = 2 * (position.y / screenSize.y) - 1;
	return tempPosCoord;
}

glm::vec3 SpriteBatch::ColorToGLCoord(glm::vec3 color)
{
	glm::vec3 tempColor;
	tempColor.r = color.r / 255.0f;
	tempColor.b = color.b / 255.0f;
	tempColor.g = color.g / 255.0f;
	return tempColor;
}

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