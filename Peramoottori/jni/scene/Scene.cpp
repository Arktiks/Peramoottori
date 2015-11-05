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
	SceneManager::GetInstance()->AddGameEntity(gameEntity, sceneNumber);
}

pm::Audio* Scene::GetAudio(std::string path)
{
	return SceneManager::GetInstance()->GetAudio(path);
}

pm::Texture* Scene::GetTexture(std::string path)
{
	return SceneManager::GetInstance()->GetTexture(path);
}
