#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include "Batch.h"
#include <GLES2\gl2.h>
#include <scene\GameEntity.h>
#include <vector>

namespace pm
{
	class SpriteBatch
	{
	public:

		static SpriteBatch* GetInstance(); ///< Return SpriteBatch instance.

		void DestroyInstance();

		void Draw(); ///< Render all batches.

		void AddGameEntity(GameEntity* gameEntity); ///< Stores given GameEntity to get patched.

		void AddOpaqueGameEntity(GameEntity* gameEntity); ///< Stores given GameEntity that is opaque to get patched.

	private:

		SpriteBatch() {}; ///< Neccessary for singleton.

		~SpriteBatch() {}; ///< Can't be deleted without calling DestroyInstance.

		bool IsDrawable(GameEntity* gameEntity); ///< Check if GameEntity is drawable.
		
		void BatchComponents();///< Makes final batch.

		/**
		* GameEntity is gutted to form data matrises that can be assimilated into Batch.
		**/
		void ParseData(GameEntity* gameEntity,
			std::vector<GLfloat>* vertexData, 
			std::vector<GLushort>* indexData,
			glm::mat4* transformMatrix,
			GLuint* textureIndex);

		std::vector<GameEntity*> gameEntityVector;
		std::vector<GameEntity*> opaqueGameEntityVector;
		std::vector<Batch> batchVector; ///< Contains all batched draw data.

		static SpriteBatch* instance;
	};
}

#endif