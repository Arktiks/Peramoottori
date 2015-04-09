#pragma once
#include <vector>
#include "GLES2\gl2.h"
#include "glm\common.hpp"
#include "glm\mat4x4.hpp"
class Sprite
{
public:
	Sprite(std::vector<GLfloat> vertexData, std::vector<GLuint> indexData,
		glm::mat4 transformMatrix, GLuint textureIndex);
	Sprite(){};
	~Sprite();

	void SetData(std::vector<GLfloat> vertexData, std::vector<GLuint> indexData,
		glm::mat4 transformMatrix, GLuint textureIndex);
private:
	std::vector<GLfloat> vertexData;
	std::vector<GLuint> indexData;
	glm::mat4 transformMatrix;
	GLuint textureIndex;
};

