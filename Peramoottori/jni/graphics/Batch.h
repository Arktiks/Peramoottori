#pragma once
#include <glm\common.hpp>
#include <glm\mat4x4.hpp>
#include <GLES2\gl2.h>
#include <vector>
class Batch
{
public:
	Batch(std::vector<GLfloat> vertexData, std::vector<GLushort> IindexData,
		glm::mat4 transformMatrix, GLuint textureIndex);
	~Batch();

	void AddData(std::vector <GLfloat> vertexDataToAdd, std::vector<GLushort>indexDataToAdd,
		glm::mat4 transformMatrix);

	std::vector<GLfloat> GetVertexData(){ return totalVertexData; }
	std::vector<GLushort> GetIndexData(){ return totalIndexData; }

	std::vector<GLfloat> totalVertexData;
	std::vector<GLushort> totalIndexData;
	std::vector<glm::mat4> transformMatrixVector;
	GLuint textureIndex;
};

