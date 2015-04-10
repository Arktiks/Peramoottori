#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <glm\common.hpp>
#include <glm\mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <EGL\egl.h>
#include <GLES2\gl2.h>
#include <vector>
#include <core\Passert.h>
#include <core\Log.h>
#include <core\Memory.h>
#include "Batch.h"
#include "Shader.h"
#include "Buffer.h"
#include "core\Game.h"

namespace pm
{

	class RenderSystem
	{
	public:
		static RenderSystem* GetInstance();
		void DestroyInstance();


		void Draw(Batch batch);	// DATA FOR ONE SPRITEBATCH "BATCH"
		void Initialize();		// Initialize when context is ready
	private:
		static RenderSystem* instance;
		RenderSystem();
		~RenderSystem();
		void CreateShaders();	// Creating shaderprogram, may be changed
		void BindBuffers(std::vector<GLfloat> vertexData, std::vector<GLuint> indexData);
		Shader shaderProgram;
		Buffer vertexBuffer, indexBuffer;

	};
}
#endif