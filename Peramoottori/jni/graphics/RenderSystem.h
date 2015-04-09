#pragma once
#include <glm\common.hpp>
#include <glm\mat4x4.hpp>
#include <EGL\egl.h>
#include <GLES2\gl2.h>
#include <vector>
#include <core\Passert.h>
#include <core\Log.h>
#include <core\Memory.h>
#include "Batch.h"
#include "Shader.h"
#include "Buffer.h"

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();
	
	void Draw(Batch batch);	// DATA FOR ONE SPRITEBATCH "BATCH"
	void Initialize();		// Initialize when context is ready
private:
	void CreateShaders();	// Creating shaderprogram, may be changed
	void BindBuffers(std::vector<GLfloat> vertexData, std::vector<GLuint> indexData);
	Shader shaderProgram;
	Buffer vertexBuffer, indexBuffer;
	
};

