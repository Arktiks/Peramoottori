#include "Application.h"

void android_main(struct android_app* state)
{
	Application peramoottori;
	peramoottori.Initialize(state);

    while (true)
	{
		struct android_poll_source* source;
		peramoottori.Update(source);
    }
}