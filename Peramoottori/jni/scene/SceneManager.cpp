#include "SceneManager.h"

using namespace pm;

SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = NEW SceneManager();
	}
	return instance;
}

void SceneManager::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}

Audio* SceneManager::GetAudio(std::string path)
{
	pm::Audio* temp = nullptr;
	for (AMI = audioVector.begin(); AMI != audioVector.end(); AMI++)
	{
		if (AMI->path == path)
		{
			temp = AMI->audio;
			return temp;
		}
		else
		{
			return temp;
		}
	}
}

Texture* SceneManager::GetTexture(std::string path)
{
	pm::Texture* temp = nullptr;
	for (TMI = textureVector.begin(); TMI != textureVector.end(); TMI++)
	{
		if (TMI->path == path)
		{
			temp = TMI->texture;
			return temp;
		}
		else
		{
			return temp;
		}
	}
}

void SceneManager::DeleteScene(int inScenenumber)
{
	int sceneNum = inScenenumber;

	for (TMI = textureVector.begin(); TMI != textureVector.end(); TMI++)
	{
		if (TMI->scene == sceneNum)
		{
			if (TMI->num == 1)
			{
				delete TMI->texture;
				TextureFactory::RemoveTexture(TMI->path);
				TMI = textureVector.erase(TMI);
			}
			else
				TMI->num--;
		}
	}

	for (AMI = audioVector.begin(); AMI != audioVector.end(); AMI++)
	{
		if (AMI->scene == sceneNum)
		{
			if (AMI->num == 1)
			{
				delete AMI->audio;
				AMI = audioVector.erase(AMI);
			}
			else
				AMI->num--;
		}
	}

	for (GEVI = gameEntityVector.begin(); GEVI != gameEntityVector.end(); GEVI++)
	{
		if (GEVI->scene == sceneNum)
		{
			delete GEVI->gameEntity;
			GEVI = gameEntityVector.erase(GEVI);
		}
	}
}

void SceneManager::AddAudio(pm::Audio* audio, int scene)
{
	for (AMI = audioVector.begin(); AMI != audioVector.end(); AMI++)
	{
		if (AMI->path == audio->GetFile())
		{
			AMI->num++;
			return;
		}
	}

	AudioStruct AS;
	AS.audio;
	AS.num = 1;
	AS.scene = scene;
	AS.path = audio->GetFile();
	audioVector.push_back(AS);
}

void SceneManager::AddTexture(pm::Texture* texture, int scene)
{
	for (TMI = textureVector.begin(); TMI != textureVector.end(); TMI++)
	{
		if (TMI->path == texture->GetFile())
		{
			TMI->num++;
		}
	}

	TextureStruct TS;
	TS.texture;
	TS.num = 1;
	TS.scene = scene;
	TS.path = texture->GetFile();
	textureVector.push_back(TS);
}

void SceneManager::AddGameEntity(pm::GameEntity* gameEntity, int scene)
{
	GameEntityStruct GES;
	GES.scene = scene;
	GES.gameEntity = gameEntity;
	gameEntityVector.push_back(GES);
}
