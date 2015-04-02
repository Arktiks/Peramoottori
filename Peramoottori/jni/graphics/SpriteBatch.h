#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include "../scene/GameEntity.h"
#include "Sprite.h"
#include "Shader.h"
#include "Batch.h"
#include <vector>
#include <glm\common.hpp>
#include <EGL\egl.h>
#include <GLES2\gl2.h>

// TODO: More pointers, and decision where data will be on one vector.


namespace pm
{
	class SpriteBatch
	{
	public:
		static SpriteBatch* GetInstance();
		void DestroyInstance();
		void AddGameEntityToVector(GameEntity *gameEntity);
		virtual ~SpriteBatch() {};
	
	private:
		SpriteBatch();
		static SpriteBatch* instance;
		// Tarkastetaan piirret‰‰nkˆ GameEntity‰
		bool CheckIfDrawable(GameEntity *gameEntity);
		// Ker‰‰ componenteilta datan jotta se voidaan batchata.
		Sprite GatherDataFromComponents(GameEntity *gameEntity);
		// Lis‰‰ GameEntityn komponenteista koodun drawablen oikeaan batchiin.
		void AddSpriteToBatch(Sprite sprite);

		std::vector<GameEntity*> gameEntityVector; 
		std::vector<Batch> batchVector;

	};
}

#endif