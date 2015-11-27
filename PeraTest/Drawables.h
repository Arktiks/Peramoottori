#pragma once
#include "Scene.h"
#include <scene\Camera.h>
#include <core\Time.h>

class Drawables : public Scene
{
public:
	Drawables();
	~Drawables();

	void Pause() override;
	void Resume() override;
	void Update() override;
	void Initialise() override;

	const unsigned int SQUARES = 10;
	const unsigned int MAX_WIDTH = 110;
	const unsigned int MAX_HEIGHT = 100;

private:
	float Random(int max); // Integer between 1 and max.
	float Random(); // Float between 0 and 1.

	float rotation;
	
	const int CAMERA_MOVE = 100;
	int camera_direction;
	int zoom_direction;

	pm::Camera* camera;
	pm::Time clock;
};