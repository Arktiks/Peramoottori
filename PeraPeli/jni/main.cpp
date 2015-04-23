#include <core\Game.h>

using namespace pm;

static float red = 0;

void android_main(struct android_app* state)
{
	Game::GetInstance()->Initialize(state);

	while (Game::GetInstance()->Update())
	{
		if (red < 255)
			red += 1;
		else
			red = 0;

		Game::GetInstance()->SetClearColor(red, 0, 0);

		Game::GetInstance()->Clear();
		Game::GetInstance()->Draw();
	}

}