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

		static SpriteBatch* instance;

		SpriteBatch() {}; ///< Neccessary for singleton.

		~SpriteBatch() {}; ///< Can't be deleted without calling DestroyInstance.

		/// Check if GameEntity is drawable.
		bool CheckIfDrawable(GameEntity* gameEntity);

		/// Gather data from components so they can be batched.
		Sprite GatherDataFromComponents(GameEntity* gameEntity);

		void AddSpriteToBatch(Sprite sprite);

		/// Add data gathered from GameEntities to batch.
		std::vector<GLfloat> CreateVertexData(std::vector<GLfloat> vertexPos,
			GLfloat depth,
			std::vector<GLfloat> vertexTexPos,
			glm::vec4 vertexColor);

		std::vector<GameEntity*> gameEntityVector;

		std::vector<Batch> batchVector; ///< Contains all batched draw data?

	};
}

#endif