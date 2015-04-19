#pragma once
#include <glm\mat4x4.hpp>
#include <GLES2\gl2.h>
#include <vector>

// Needs more commentating!

namespace pm
{
	class Batch
	{
	public:
		
		Batch() : textureIndex(0) {};

		Batch(std::vector<GLfloat> vertexData,
			std::vector<GLushort> indexData,
			glm::mat4 transformMatrix,
			GLuint textureIndex);

		// In case default constructor was used?
		// New data to add to batch. Texture cannot be changed.
		void AddData(std::vector <GLfloat> vertexData,
			std::vector<GLushort>indexData,
			glm::mat4 transformMatrix);


		/// Are these functions neccessary?
		std::vector<GLfloat> GetVertexData() { return totalVertexData; }
		std::vector<GLushort> GetIndexData(){ return totalIndexData; }


		std::vector<GLfloat> totalVertexData;
		std::vector<GLushort> totalIndexData;
		std::vector<glm::mat4> transformMatrixVector;
		GLuint textureIndex;
	};
}