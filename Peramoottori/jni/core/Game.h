#ifndef GAME_H
#define GAME_H

#include <core\Application.h>
#include <core\Vector2.h>
#include "scene\GameEntity.h"
#include "graphics\SpriteBatch.h"

#include "graphics\Rectangle.h"
#include "scene\Texture.h"
#include "graphics\Color.h"
#include "scene\Transformable.h"
#include "graphics\Drawable.h"

namespace pm
{
	class Game : public Application
	{
	public:

		/// Return only instance of Game. 
		/// Only one instance of Game should exist during runtime.
		static Game* GetInstance();

	public:

		void DestroyInstance(); ///< Deletes Game instance.

		bool Initialize(android_app* application); ///< Needs to be called to setup Perämoottori.

		void InitializeGame();

		bool IsReady(); ///< Return true if Game is ready to be updated and drawn.

		Vector2<int> GetResolution(); ///< Return display resolution.

		void Clear(); ///< Clear display with clear color.

		void SetClearColor(float red, float green, float blue);

		bool Update(); ///< Updates neccessary android calls.

		void UpdateGame();

		void Draw(); // !!! Scene will remove this later.

	private:


		bool initialized; ///< Checks if Initialize has been called succesfully at least once.

		Game() : Application(), initialized(false) {};

		~Game() {};

		static Game* instance; ///< Pointer to only instance of the class.

		GameEntity gameEntity;
	};
}

#endif