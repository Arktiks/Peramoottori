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



	/** \brief Scene class contains scenes that can store Audio, Textures and GameObjects.
	*
	* \ingroup Scene
	*/
	class Scene
	{
	protected:

	//using gameEntityVector =  std::vector<GameEntity*>;
	//using GEVI = std::vector<GameEntity*>::iterator;

		struct GameEntityStruct
		{
			int scene;
			pm::GameEntity* gameEntity;
		};

	public:

		/** \brief Scene constructor
		* Sets unique sceneNumber from SceneManager
		*/
		Scene();

		/** \brief Scene destructor
		* Deletes all stored GameEntitys and removes 
		*/
		~Scene();

		/** \brief Adds new Audio object.
		*
		* Audio is stored in a vector.
		*/
		void AddAudio(Audio*);

		/** \brief Adds new Texture object.
		*
		* Texture is stored in a vector.
		*/
		void AddTexture(Texture*);

		/** \brief Adds new GameEntity object.
		*
		* GameEntity is stored in a vector.
		*/
		void AddGameEntity(pm::GameEntity*);

		/** \brief Returns the Audio pointer with path param .
		* \param[in] string audioPath.
		* Used for getting Audio pointer with the param path.
		* \return Audio pointer
		*/
		pm::Audio* GetAudio(std::string);

		/** \brief Returns the Texture pointer with path param .
		* \param[in] string texturePath.
		* Used for getting Texture pointer with the param path.
		* \return Audio Texture
		*/
		pm::Texture* GetTexture(std::string);

		/** \brief Creates new T pointer.
		* Used for creating T pointer and stores it.
		* \return T pointer.
		*/
		template<typename T> T* Create();

		/** \brief Returns int scene number.
		* Used for getting scene number.
		* \return int scene number.
		*/
		int GetSceneNumber(){ return sceneNumber; };

		/** \brief Returns vector of GameEntitys.
		* Used for getting vector of GameEntitys.
		* \return vector of GameEntitys.
		*/		
		const std::vector<GameEntity*> GetGameEntityVector() const
		{ return gameEntityVector; };

	private:

		int sceneNumber;

		std::vector<GameEntity*> gameEntityVector;
		std::vector<GameEntity*>::iterator GEVI;
	};
};

template<typename T>
T* pm::Scene::Create()
{
	T* tempTemplate = NEW T();
	gameEntityVector.push_back(tempTemplate);
	return tempTemplate;
}

#endif