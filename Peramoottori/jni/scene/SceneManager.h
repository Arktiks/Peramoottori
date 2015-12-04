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
	/** \brief Scene class manages scenes.
	* All objects in scenes are stored here so scenes can share objects 
	* \ingroup Scene
	*/
	class SceneManager
	{

	public:

		/** \brief Return instace of SceneManager.
		*/
		static SceneManager* GetInstance();

		/** \brief Destroys instace of SceneManager.
		*/
		void DestroyInstance();


		/** \brief Adds Audio object to vector.
		* Is called from scene.
		* \param[in] audio pointer.
		* \param[in] int sceneNumber.
		*/
		void AddAudio(pm::Audio*, int);

		/** \brief Adds Texture object to vector.
		* Is called from scene.
		* \param[in] audio pointer.
		* \param[in] int sceneNumber.
		*/
		void AddTexture(pm::Texture*, int);

		/** \brief Adds GameEntity to vector.
		* Is called from scene.
		* \param[in] audio pointer.
		* \param[in] int sceneNumber.
		*/
		void AddGameEntity(pm::GameEntity*, int);

		/** \brief Returns Audio pointer of the specified by the path.
		*
		* Mainly used for Audio pointers from scenes.
		* \param[in] string audio path.
		* \return audio pointer.
		*/
		pm::Audio* GetAudio(std::string);

		/** \brief Returns Texture pointer of the specified by the path.
		*
		* Mainly used for Texture pointers from scenes.
		* \param[in] string Texture path.
		* \return Texture pointer.
		*/
		pm::Texture* GetTexture(std::string);

		/** \brief Deletes selected scene.
		*
		* Used to erase scene spesific objects and the scene itself.
		* \param[in] int scene number.
		*/
		void DeleteScene(int);

		/** \brief Returns the number of scenes.
		*
		* Used to get the number of scenes.
		* \return int sceneSum.
		*/
		int GetSceneSum(){ return sceneSum; };

		/** \brief Increases number of scenes.
		* Scene calls this when it is createdt to get a unique scene number
		* Used to sceneSum++.
		*/
		void SceneSumPlusPlus(){ sceneSum++; };

	protected:

		/** AudioStruct 
		*  Used to store Audio pointer and associated information.
		*/
		struct AudioStruct
		{
			std::string path;
			int scene;
			pm::Audio* audio;
			int num;
		};

		/** TextureStruct
		*  Used to store Texture pointer and associated information.
		*/
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
