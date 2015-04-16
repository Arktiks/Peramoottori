#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <GLES2\gl2.h>
#include <glm\mat4x4.hpp>

namespace pm
{
	class Sprite
	{
	public:
	Sprite(std::vector<GLfloat> vertexData, std::vector<GLushort> indexData,

	void SetData(std::vector<GLfloat> vertexData, std::vector<GLushort> indexData,

		Sprite(std::vector<GLfloat> vertexData,
			std::vector<GLuint> indexData,
			glm::mat4 transformMatrix,
			GLuint textureIndex);

		void SetData(std::vector<GLfloat> vertexData,
			std::vector<GLuint> indexData,
			glm::mat4 transformMatrix,
			GLuint textureIndex);

		bool ValidateData();

		~Sprite() {};

		std::vector<GLfloat> GetVertexData() { return vertexData; }
		std::vector<GLuint> GetIndexData() { return indexData; }
		glm::mat4 GetTransformMatrix() { return transformMatrix; }
		GLuint GetTextureIndex() { return textureIndex; }

	std::vector<GLushort> GetIndexData(){ return indexData; };
	private:

		std::vector<GLfloat> vertexData;
	std::vector<GLushort> indexData;
		glm::mat4 transformMatrix;
		GLuint textureIndex;
	};
}

#endif