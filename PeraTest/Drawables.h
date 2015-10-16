#pragma once
#include "Scene.h"

class Drawables : public Scene
{
public:
	Drawables();
	~Drawables();

	void Pause();
	void Resume();
	void Update();
	void Initialise();

	const unsigned int SQUARES = 25;
	const unsigned int MAX_WIDTH = 110;
	const unsigned int MAX_HEIGHT = 100;

private:
	float Random(int max); // Number between 1 and max.
	float Random();

	float rotation;
};