#include <android_native_app_glue.h>
#include <core\Game.h>

using namespace pm;

static float red = 0.0f;

void android_main(struct android_app* state)
{
	Game::GetInstance()->Initialize(state);

	while (Game::GetInstance()->Update())
	{
		if (red < 255.0f)
			red += 1.0f;
		else
			red = 0.0f;

		Game::GetInstance()->SetClearColor(red, 0.f, 1.f);

		Game::GetInstance()->Clear();
		Game::GetInstance()->Draw();
	}

}