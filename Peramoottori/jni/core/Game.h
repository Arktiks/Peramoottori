#ifndef GAME_H
#define GAME_H

#include <core\Application.h>
#include <core\Vector2.h>

namespace pm
{
	class Game : private Application
	{
	public:
		Game();

		Game(android_app* application);

		bool Initialize(android_app* application);

		Vector2<int> GetResolution();

		void Clear();

		void SetClearColor(float red, float green, float blue);

		bool IsReady();

		bool Update();

		void Draw();

		~Game();

	private:

		void AddInstance();

		static std::size_t instances;

	};
}

#endif