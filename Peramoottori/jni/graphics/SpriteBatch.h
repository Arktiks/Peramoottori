#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include "Sprite.h"
#include "Shader.h"
#include "Batch.h"
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
		void Initialize();
		void DestroyInstance();
		
		void addSprite(std::vector<GLfloat> vertexData, std::vector<GLuint> indexData,
			glm::mat4 transformMatrix, GLuint textureIndex);		// Sprite format will be changed
		void Draw();

		virtual ~SpriteBatch() {};
	

	private:

		SpriteBatch();
		static SpriteBatch* instance;

		void Update();
		void Sort();
		void BindBuffers();
		void CreateBufferData();
		void CreateShaders();

		std::vector<GLfloat> createGLCoord(std::vector<GLfloat> convertVertices, glm::vec2 textureSize);
		glm::vec2 PositionToGLCoord(glm::vec2 position);
		glm::vec3 ColorToGLCoord(glm::vec3 color);
		glm::vec2 TextureToGLCoord(glm::vec2 position, glm::vec2 spriteSize);

		glm::vec2 screenSize;

		std::vector<Sprite*> sprites; // Saadaanko spritet lisättyä automaattisesti tähän listaan?
		std::vector<GLuint> indexData;
		std::vector<GLfloat> vertexData;

		std::vector<Batch> batchVector;

		// Todennäköisesti muuttuvat:


		int spriteAmount;
		GLuint buffer[2];
		Shader defaultShader;
	};
}

#endif