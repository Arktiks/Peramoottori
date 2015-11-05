#ifndef SCENE_H
#define SCENE_H

#include <scene\Texture.h>
#include <audio\Audio.h>
#include <scene\GameEntity.h>
#include <core\Memory.h>
#include <scene\SceneManager.h>

#include <scene\Scene.h>

#include <map>
#include <string>
#include <vector>

namespace pm
{
	class Scene
	{

	public:

		Scene();

		~Scene();


		void AddAudio(Audio*);

		void AddTexture(Texture*);

		void AddGameEntity(pm::GameEntity*);


		pm::Audio* GetAudio(std::string);

		pm::Texture* GetTexture(std::string);


		int GetSceneNumber(){ return sceneNumber; };

	private:

		int sceneNumber;

	};
};
#endif