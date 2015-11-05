#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <audio\Audio.h>
#include <scene\GameEntity.h>
#include <core\Memory.h>
#include <resources\TextureFactory.h>

#include <map>
#include <string>
#include <vector>

namespace pm
{
	class SceneManager
	{

	public:

		static SceneManager* GetInstance();

		void DestroyInstance();


		void AddAudio(pm::Audio*, int);
		void AddTexture(pm::Texture*, int);
		void AddGameEntity(pm::GameEntity*, int);


		pm::Audio* GetAudio(std::string);
		pm::Texture* GetTexture(std::string);


		void DeleteScene(int);

		int GetSceneSum(){ return sceneSum; };
		void SceneSumPlusPlus(){ sceneSum++; };

	protected:

		struct AudioStruct
		{
			std::string path;
			int scene;
			pm::Audio* audio;
			int num;
		};

		struct TextureStruct
		{
			std::string path;
			int scene;
			pm::Texture* texture;
			int num;
		};

	private:

		SceneManager() { sceneSum = 0; }; ///< Neccessary for singleton.

		~SceneManager() {}; ///< Can't be deleted without calling DestroyInstance.

		std::vector<TextureStruct> textureVector;
		std::vector<TextureStruct>::iterator TMI;

		std::vector<AudioStruct> audioVector;
		std::vector<AudioStruct>::iterator AMI;

		int sceneSum;

		static SceneManager *instance;
	};
};
#endif //SCENEMANAGER_H
