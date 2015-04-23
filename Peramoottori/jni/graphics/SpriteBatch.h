#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include "Sprite.h"
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

		static SpriteBatch* GetInstance();

		void DestroyInstance();

		void Draw();

		void AddGameEntity(GameEntity* gameEntity);

	private:

		SpriteBatch() {}; ///< Neccessary for singleton.

		~SpriteBatch() {}; ///< Can't be deleted without calling DestroyInstance.

		bool IsDrawable(GameEntity* gameEntity); ///< Check if GameEntity is drawable.
		
		void BatchComponents();
		void ParseData(GameEntity* gameEntity,
			std::vector<GLfloat>* vertexData, 
			std::vector<GLushort>* indexData,
			glm::mat4* transformMatrix,
			GLuint* textureIndex);



		std::vector<GameEntity*> gameEntityVector;

		std::vector<Batch> batchVector; ///< Contains all batched draw data?

		static SpriteBatch* instance;

	};
}

#endif