#include "SpriteBatch.h"
#include <algorithm>
// TODO: Tuki indeksimäärältään erikokoisille spriteille tehdään piirtämällä kolmioita vain.
// Spritebatcheja on vain yksi, singleton? 
// Tämän kautta piirretään kaikki



SpriteBatch::SpriteBatch()
{
	screenSize = glm::vec2(500, 500); // !!!!! Get real screen resolution!
	spriteAmount = 0;
	glGenBuffers(2, &buffer[0]);
}


SpriteBatch::~SpriteBatch()
{

}

void addSprite(Sprite &sprite)
{
	sprites.push_back(sprite);
}

void SpriteBatch::Draw()
{
	// Draws textures that are in same layer. TODO: Add texture-sort to sort-function
	if (sprites.size != 0)
	{
		GLuint currentAtlasIndex = sprites[0]->texture.atlasIndex;
		
		unsigned totalIndiceAmount = 0;
		unsigned indiceAmount = sprites[0]->indices.size();
	
		for (unsigned i = 0; i < sprites.size(); i++)
		{
			if (i+1 != sprites.end())
			{
				glBindTexture(GL_TEXTURE_2D, currentAtlasIndex);
				glDrawElements(GL_TRIANGLES, indiceAmount, GL_UNSIGNED_INT,
					reinterpret_cast<GLvoid*>(totalIndices) * sizeof(GLuint));
				glBindTexture(GL_TEXTURE_2D, 0u);
				break;
			}
			else if (sprites[i + 1]->texture.atlasIndex == currentAtlasIndex;)
			{
				indiceAmount += sprites[i+1]->indices.size();
			}
			else
			{
				//draw sprites with last texture, set new texture and current indiceAmount to totalIndices.
				glBindTexture(GL_TEXTURE_2D, currentAtlasIndex);
				glDrawElements(GL_TRIANGLES, indiceAmount, GL_UNSIGNED_INT,
					reinterpret_cast<GLvoid*>(totalIndiceAmount) *sizeof(GLuint));
				glBindTexture(GL_TEXTURE_2D, 0u);

				totalIndiceAmount += indiceAmount;
				indiceAmount = sprites[i+1]->indices.size();
				currentAtlasIndex = sprites[i + 1]->texture.atlasIndex;
			}
		}
	}
}

void SpriteBatch::Update()
{
	CreateBufferData();

	if (spriteAmount != sprites.size())
	{
		spriteAmount = sprites.size();
		// Buffereille voitaisiin tehdä oma funktio/luokka?
		glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
		glBufferData(GL_ARRAY_BUFFER, vertexData.size()*sizeof(GLfloat), &vertexData.front(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size()*sizeof(GLuint), &indexData.front(), GL_DYNAMIC_DRAW);
	}
	
	glBufferSubData(GL_ARRAY_BUFFER, 0u, vertexData.size()*sizeof(GLfloat), &vertexData.front());
}
/// Spritebatch vector sort
/**
	Sorts sprites according to their draw depth.
*/
void SpriteBatch::Sort()
{
	for (std::vector<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++)
	{
		std::sort(sprites.begin(), sprites.end(),
			[](Sprite a, Sprite b ){return (a.drawDepht > b.drawDepht); });
	}
}

void SpriteBatch::CreateBufferData()
{
	indexData.clear();
	vertexData.clear();

	// add current vector to indexData, sort should have been called before this.
	for (unsigned i = 0; i < sprites.size(); i++)
	{
		indexData.insert(indexData.end(), sprites[i]->indices.begin(), sprites[i]->indices.end());

		std::vector<GLfloat> tempVertices = createGLCoord(sprites[i]->vertices, sprites[i]->texture.getTextureSize());	// Tarkasta textureSize että palauttaa oikean.
		vertexData.insert(vertexData.end(), tempVertexData.begin(), tempVertexData.end());
	}
}

std::vector<GLfloat> createGLCoord(std::vector<GLfloat> convertVertices, glm::vec2 textureSize)
{	
	glm::vec2 position = PositionToGLCoord(glm::vec2(convertVertices[0], convertVertices[1]));
	glm::vec3 color = ColorToGLCoord(glm::vec3(convertVertices[2], convertVertices[3], convertVertices[4]));
	glm::vec2 texturePosition = TextureToGLCoord(glm::vec2(convertVertices[5], convertVertices[6], textureSize));
	
	std::vector<GLfloat> glVertexData[7];

	glVertexData[0] = position.x;
	glVertexData[1] = position.y;
	glVertexData[2] = color.r;
	glVertexData[3] = color.b;
	glVertexData[4] = color.g;
	glVertexData[5] = texturePosition.x;
	glVertexData[6] = texturePosition.y;

	return glVertexData;
}

glm::vec2 SpriteBatch::TextureToGLCoord(glm::vec2 position, glm::vec2 spriteSize)
{
	glm::vec2 tempTexCoord;
	tempTexCoord.x = position.x / spriteSize.x;
	tempTexCoord.y = position.y / spriteSize.y;
	return tempTexCoord;

}
glm::vec2 SpriteBatch::PositionToGlCoord(glm::vec2 position)
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

// Todennäköisesti muuttuvat:
void TempCreateShader()
{

}