#pragma once
#include "Scene.h"
#include <graphics\Text.h>
#include <vector>

class Texts : public Scene
{
public:
	Texts();
	~Texts();
	void Update() override;

	std::vector<pm::Text*> texts;
};