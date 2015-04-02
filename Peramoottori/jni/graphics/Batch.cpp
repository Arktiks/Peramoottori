#include "Batch.h"

Batch::Batch(std::vector<GLfloat> vertexData, std::vector<GLuint> indexData,
	glm::mat4 transformMatrix, GLuint textureIndex)
{
	totalVertexData = vertexData;
	totalIndexData = indexData;
	transformMatrixVector.push_back(transformMatrix);
	textureIndex = textureIndex;
}

// New data to add to batch. Texture cannot be changed.
void Batch::AddData(std::vector <GLfloat> vertexDataToAdd, std::vector<GLuint>indexDataToAdd,
	glm::mat4 transformMatrix)
{
	totalVertexData.insert(totalVertexData.end(), vertexDataToAdd.begin(), vertexDataToAdd.end());
	totalIndexData.insert(totalIndexData.end(), indexDataToAdd.begin(), indexDataToAdd.end());
	transformMatrixVector.push_back(transformMatrix);
}

Batch::~Batch()
{
}
