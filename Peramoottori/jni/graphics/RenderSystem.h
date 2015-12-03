#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <vector>
#include <GLES2\gl2.h>

#include "scene\CameraSystem.h"
#include "Batch.h"
#include "Shader.h"
#include "Buffer.h"

namespace pm
{
	/** \brief System that contains necessary data (shader, camera, etc.) for rendering.
	*
	* pm::Application handles the lifeline of %RenderSystem.
	*
	* \sa pm::SpriteBatch contains all necessary functions for rendering GameEntities.
	*
	* \ingroup Graphics
	*/

	class RenderSystem
	{
	public:

		friend class SpriteBatch;
		friend class Application;
		friend class CommandCenter;

		/** \brief Return instance of RenderSystem. 
		* \return Pointer to RenderSystem.
		*/
		static RenderSystem* GetInstance();

		/** \internal Following four functions set private as not to confuse user.
		* For example RenderSystem and SpriteBatch both have Draw().
		* Also public Initialize function might imply user needs to initialize RenderSystem himself. */
	private:
		void DestroyInstance(); /// Removes current instance.

		void Initialize(); ///< RenderSystem should be initialized when context is ready.
		

		void Draw(Batch* batch, Shader* shader);///< renders one patch.
		void Draw(Batch* batch); ///< renders one patch.

		bool IsInitialized();


		RenderSystem() : shaderProgram(), vertexBuffer(), indexBuffer() {};

		void BindBuffers(Batch* batch); ///< Binds buffers before rendering patch.

		void CreateShaders(); // May be changed.
		
		//CameraSystem* cameraSystem;
		
		GLint transformMatrixLocation;
		GLint cameraMatrixLocation;
		GLint projectionLocation;
		
		Shader shaderProgram;
		Shader textShaderProgram;

		Buffer vertexBuffer, indexBuffer;

		static RenderSystem* instance;

		static bool initialized;

		~RenderSystem();
	};
}

#endif