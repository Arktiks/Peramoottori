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
		Sprite(std::vector<GLfloat> vertexData,
			std::vector<GLushort> indexData,
			glm::mat4 transformMatrix,
			GLuint textureIndex);

		void SetData(std::vector<GLfloat> vertexData,
			std::vector<GLushort> indexData,
			glm::mat4 transformMatrix,
			GLuint textureIndex);

		std::vector<GLfloat> GetVertexData() { return vertexData; }
		std::vector<GLushort> GetIndexData(){ return indexData; }
		glm::mat4 GetTransformMatrix() { return transformMatrix; }
		GLuint GetTextureIndex() { return textureIndex; }

	private:

		/// Error handling.
		bool ValidateData();

		std::vector<GLfloat> vertexData;
		std::vector<GLushort> indexData;
		glm::mat4 transformMatrix;
		GLuint textureIndex;
	};
}

#endif