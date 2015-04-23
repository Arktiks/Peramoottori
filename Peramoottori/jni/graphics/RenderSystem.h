#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <vector>
#include <GLES2\gl2.h>

#include "Batch.h"
#include "Shader.h"
#include "Buffer.h"

namespace pm
{
	class RenderSystem
	{
	public:
		static RenderSystem* GetInstance();

		void DestroyInstance();

		void Initialize(); ///< RenderSystem should be initialized when context is ready.

		void Draw(Batch* batch);

	private:

		RenderSystem() : shaderProgram(), vertexBuffer(), indexBuffer() {};

		~RenderSystem() {};

		void BindBuffers(Batch* batch);

		void CreateShaders(); // May be changed.

		Shader shaderProgram;

		Buffer vertexBuffer, indexBuffer;

		static RenderSystem* instance;

	};
}
#endif