#include "Scene.h"
using namespace pm;

Scene::~Scene()
{
	// May cause problems.
	//for (std::vector<GameEntity*>::iterator it = entities.begin(); it != entities.end(); it++)
		//delete (*it);
}

void Scene::Pause()
{
	pause = true;
}

void Scene::Resume()
{
	pause = false;
}

void Scene::Update()
{
}

void Scene::Initialise()
{
}