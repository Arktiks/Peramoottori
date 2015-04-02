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

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();
	
	void Draw(Batch batch);	// DATA FOR ONE SPRITEBATCH "BATCH"
private:
	void CreateShaders();	// Creating shaderprogram, may be changed
	Shader shaderProgram;
	GLuint buffer[2];
	
};

