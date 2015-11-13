#pragma once
#include <vector>
#include <scene\GameEntity.h>
#include <core\Input.h>
#include <string>

// Works as base for all test scenes.

class Scene
{
public:
	Scene() = delete;
	Scene(std::string name) : name(name), pause(false) {};
	virtual ~Scene();

	virtual void Pause();
	virtual void Resume();
	virtual void Update() = 0;
	virtual void Initialise();

	std::string name;
	bool pause;
	std::vector<pm::GameEntity*> entities;
	pm::Input input;
};