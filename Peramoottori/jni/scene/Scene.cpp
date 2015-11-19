#include "Scene.h"

using namespace pm;

Scene::Scene()
{	
	this->sceneNumber = SceneManager::GetInstance()->GetSceneSum();
	SceneManager::GetInstance()->SceneSumPlusPlus();
}

Scene::~Scene()
{
	SceneManager::GetInstance()->DeleteScene(sceneNumber);

	for (GEVI = gameEntityVector.begin(); GEVI != gameEntityVector.end();)
	{
		delete *GEVI;
		GEVI = gameEntityVector.erase(GEVI);
	}
}

void Scene::AddAudio(pm::Audio* audio)
{
	SceneManager::GetInstance()->AddAudio(audio, sceneNumber);
}

void Scene::AddTexture(pm::Texture* texture)
{
	SceneManager::GetInstance()->AddTexture(texture, sceneNumber);
}

void Scene::AddGameEntity(pm::GameEntity* gameEntity)
{
	gameEntityVector.push_back(gameEntity);
}

void Scene::RemoveGameEntity(pm::GameEntity* gameEntity)
{

	for (std::vector<pm::GameEntity*>::iterator it = gameEntityVector.begin(); it != gameEntityVector.end();)
	{
		if (*it == gameEntity)
		{
			delete *it;
			it = gameEntityVector.erase(it);
			break;
		}
		else
			it++;
	}
}

pm::Audio* Scene::GetAudio(std::string path)
{
	return SceneManager::GetInstance()->GetAudio(path);
}

pm::Texture* Scene::GetTexture(std::string path)
{
	return SceneManager::GetInstance()->GetTexture(path);
}


