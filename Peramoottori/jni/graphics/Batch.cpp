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
	// Indexit asetetaan oikeiksi arvoiksi sen mukaan montako spriteä on batchissä.
	unsigned size = (totalIndexData.size() / 6) * 4;
	totalIndexData.push_back(indexData[0] + size);
	totalIndexData.push_back(indexData[1] + size);
	totalIndexData.push_back(indexData[2] + size);
	totalIndexData.push_back(indexData[3] + size);
	totalIndexData.push_back(indexData[4] + size);
	totalIndexData.push_back(indexData[5] + size);

	transformMatrixVector.push_back(transformMatrix);
}