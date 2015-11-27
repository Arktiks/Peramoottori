#include "Scene.h"
using namespace pm;

Scene::~Scene()
{
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