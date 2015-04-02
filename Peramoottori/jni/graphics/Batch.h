#pragma once
#include <glm\common.hpp>
#include <glm\mat4x4.hpp>
#include <GLES2\gl2.h>
#include <vector>
class Batch
{
public:
	Batch(std::vector<GLfloat> vertexData, std::vector<GLuint> IindexData,
		glm::mat4 transformMatrix, GLuint textureIndex);
	~Batch();

	void AddData(std::vector <GLfloat> vertexDataToAdd, std::vector<GLuint>indexDataToAdd,
		glm::mat4 transformMatrix);

	std::vector<GLfloat> totalVertexData;
	std::vector<GLuint> totalIndexData;
	std::vector<glm::mat4> transformMatrixVector;
	GLuint textureIndex;
};

