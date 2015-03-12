#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include "Sprite.h"

#include <vector>
#include <glm\common.hpp>
#include <EGL\egl.h>
#include <GLES2\gl2.h>

namespace pm
{
	class SpriteBatch
	{
	public:
		static SpriteBatch* GetInstance();
		void DestroyInstance();
		void Draw();
		void Initialize(glm::vec2 screenSize);
		void addSprite(Sprite *sprite);
		virtual ~SpriteBatch(){};
	private:
		SpriteBatch();
		static SpriteBatch* instance;

		void Update();
		void CreateBufferData();
		void BindBuffers();
		void Sort();
		std::vector<GLfloat> createGLCoord(std::vector<GLfloat> convertVertices, glm::vec2 textureSize);
		glm::vec2 PositionToGLCoord(glm::vec2 position);
		glm::vec3 ColorToGLCoord(glm::vec3 color);
		glm::vec2 TextureToGLCoord(glm::vec2 position, glm::vec2 spriteSize);

		glm::vec2 screenSize;

		std::vector<Sprite*> sprites; // Saadaanko spritet lisättyä automaattisesti tähän listaan?
		std::vector<GLuint> indexData;
		std::vector<GLfloat> vertexData;

		// Todennäköisesti muuttuvat:
	void TempCreateShader();

	GLuint glObject;
	int spriteAmount;
	GLuint buffer[2];
	};
}

#endif