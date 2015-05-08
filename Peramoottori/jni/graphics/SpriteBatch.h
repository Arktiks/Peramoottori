#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include "Batch.h"

#include <GLES2\gl2.h>
#include <scene\GameEntity.h>
#include <vector>

// Needs commentating!

namespace pm
{
	class SpriteBatch
	{
	public:

		static SpriteBatch* GetInstance(); ///< Returns Spritepatch instance 

		void DestroyInstance(); ///< Removes Spritepatch instance 

		void Draw(); ///< Renders all batches  

		void AddGameEntity(GameEntity* gameEntity); ///< Stores given GameEntity pointer to get patched.

		void AddOpaqueGameEntity(GameEntity* gameEntity); ///< Stores given GameEntity pointer, that is opaque, to get patched.

	private:

		SpriteBatch() {}; ///< Neccessary for singleton.

		~SpriteBatch() {}; ///< Can't be deleted without calling DestroyInstance.

		bool IsDrawable(GameEntity* gameEntity); ///< Check if GameEntity is drawable.
		
		void BatchComponents();///< Makest the final batch

		/**
		*GameEntity is gutted to form data matrises that can be assimilated to a Batch.
		*/
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