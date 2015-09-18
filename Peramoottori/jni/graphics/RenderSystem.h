#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <vector>
#include <GLES2\gl2.h>

#include "Batch.h"
#include <scene\Camera.h>
#include "Shader.h"
#include "Buffer.h"

namespace pm
{
	class RenderSystem
	{
	public:

		static RenderSystem* GetInstance();///< Returns RenderSystem instance, that can be only one at once.

		void SetActiveCamera(Camera* camera){ activeCamera = camera; }
		Camera* GetActiveCamera(){ return activeCamera; }

		void DestroyInstance(); /// Removes current instance.

		void Initialize(); ///< RenderSystem should be initialized when context is ready.
		
		void Draw(Batch* batch); ///< renders one patch.

		bool IsInitialized();

	private:

		RenderSystem() : shaderProgram(), vertexBuffer(), indexBuffer() {};

		void BindBuffers(Batch* batch); ///< Binds buffers before rendering patch.

		void CreateShaders(); // May be changed.

		Camera* activeCamera;

		Shader shaderProgram;

		Buffer vertexBuffer, indexBuffer;

		static RenderSystem* instance;

		static bool initialized;

		~RenderSystem();
	};
}

#endif