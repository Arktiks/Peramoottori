#pragma once
#include <glm\common.hpp>
#include <glm\mat4x4.hpp>
#include <GLES2\gl2.h>
#include <vector>

// Needs more commentating!

namespace pm
{
	class Batch
	{
	public:
		
		/// Default constructor.
		Batch() : textureIndex(0) {};

		Batch(std::vector<GLfloat> vertexData,
			std::vector<GLuint> indexData,
			glm::mat4 transformMatrix,
			GLuint textureIndex);

		// In case default constructor was used?
		void AddData(std::vector <GLfloat> vertexData,
			std::vector<GLuint>indexData,
			glm::mat4 transformMatrix);

		~Batch() {};

		std::vector<GLfloat> totalVertexData;
		std::vector<GLuint> totalIndexData;
		std::vector<glm::mat4> transformMatrixVector;
		GLuint textureIndex;
	};
}