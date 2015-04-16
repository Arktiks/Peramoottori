#include "Batch.h"

using namespace pm;

Batch::Batch(std::vector<GLfloat> vertexData,
	std::vector<GLuint> indexData,
	glm::mat4 transformMatrix,
	GLuint textureIndex)
{
	totalVertexData = vertexData;
	totalIndexData = indexData;
	transformMatrixVector.push_back(transformMatrix);
	(this->textureIndex) = textureIndex;
}

// New data to add to batch. Texture cannot be changed.
void Batch::AddData(std::vector <GLfloat> vertexData,
	std::vector<GLuint>indexData,
	glm::mat4 transformMatrix)
{
	totalVertexData.insert(totalVertexData.end(), vertexData.begin(), vertexData.end());
	totalIndexData.insert(totalIndexData.end(), indexData.begin(), indexData.end());
	transformMatrixVector.push_back(transformMatrix);
}