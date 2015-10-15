#include "SceneManager.h"
using namespace pm;

SceneManager::SceneManager() : sceneChanged(false)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update()
{
	for (std::vector<Scene*>::iterator it = scenes.begin(); it != scenes.end(); it++)
	{
		if (sceneChanged)
		{
			sceneChanged = false;
			return;
		}
		if ((*it)->pause == false)
			(*it)->Update();
	}
}

void SceneManager::AddScene(Scene* scene)
{
	scenes.push_back(scene);
}

void SceneManager::DeleteScene(std::string name)
{
	for (std::vector<Scene*>::iterator it = scenes.begin(); it != scenes.end(); it++)
	{
		if ((*it)->name == name)
		{
			delete *it;
			scenes.erase(it);
			sceneChanged = true;
		}
	}
}

Scene* SceneManager::GetScene(std::string name)
{
	for (std::vector<Scene*>::iterator it = scenes.begin(); it != scenes.end(); it++)
	{
		if ((*it)->name == name)
			return (*it);
	}

	return nullptr;
}

bool SceneManager::Paused()
{
	for (std::vector<Scene*>::iterator it = scenes.begin(); it != scenes.end(); it++)
	{
		if ((*it)->pause == false)
			return false;
	}

	return true;
}