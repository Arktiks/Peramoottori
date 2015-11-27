#pragma once
#include "Scene.h"
#include <audio\Audio.h>
#include <core\Time.h>

class Audio : public Scene
{
public:
	Audio();
	~Audio();

	void Update();
	void Pause();
	void Resume();

	pm::Audio* effect; // Effect is played between fixed intervals.
	pm::Audio* music; // Music is played continuously.

	// pm::Time clock;
};