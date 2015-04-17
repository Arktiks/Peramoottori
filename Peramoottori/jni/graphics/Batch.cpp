#include "Batch.h"

using namespace pm;
Batch::Batch(std::vector<GLfloat> vertexData,
	std::vector<GLushort> indexData,
	glm::mat4 transformMatrix,
	GLuint textureIndex)
{
	totalVertexData = vertexData;
	totalIndexData = indexData;
	transformMatrixVector.push_back(transformMatrix);
	(this->textureIndex) = textureIndex;
}

void Batch::AddData(std::vector <GLfloat> vertexData,
	std::vector<GLushort>indexData,
	glm::mat4 transformMatrix)
{
	totalVertexData.insert(totalVertexData.end(), vertexData.begin(), vertexData.end());
	totalIndexData.insert(totalIndexData.end(), indexData.begin(), indexData.end());
	transformMatrixVector.push_back(transformMatrix);
}