#pragma once
#include "Box.h"
#include "Scene.h"
#include <vector>

class Input : public Scene
{
public:
	Input();
	~Input();

	void Update() override;

	std::vector<Box*> boxes;

	int box_amount; // Amount of boxes left on the scene.
};