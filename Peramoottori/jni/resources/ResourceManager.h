#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <android\asset_manager.h>
#include <resources\Resource.h>

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <memory>

namespace pm
{
	class ResourceManager
	{

		friend class Application;

	public:

		/// Static function that returns instance pointer of ResourceManager.
		/// Only one instance of ResourceManager will exist during runtime.
		///		\return pointer to only instance of this class.
		static ResourceManager* GetInstance();
				
		/// Main resource management function for user.
		/// Checks that there won't be duplicate files.
		/// Determines type of file and calls proper function to decrypt it.
		/// Every file is converted to Resource type.
		///		\param fileName : string name of the file.
		///		\return created or loaded Resource.
		std::shared_ptr<Resource*> LoadAsset(std::string fileName);

		/// Returns content of AAsset as std::string.
		///		\param fileName : string name of AAsset.
		///		\return content of AAsset as string.
		AAsset* GetAAsset(std::string fileName);

		/// Simple public function to empty the asset std::map.
		/// Should be used when deleting previous scene.
		void ClearAssetMap();

	private:


		/// Return content of a text file as std::string.
		///		\param fileName : string name of text file.
		///		\return content of text file.
		std::string ReadText(std::string fileName);

		/// Returns vector that contains pixel data.
		/// Image is contained as unsigned char vector.
		///		\param fileName : string name of AAsset.
		///		\return content of AAsset as unsigned char vector.
		std::vector<unsigned char> ReadImage(std::string fileName);

		/// EI VIELÄ KÄYTÖSSÄ SIIRRÄ FONTIN LATAUS TÄNNE
		std::string ReadFont(std::string fileName);

		/// KORJAA
		AAsset* ReadAudio(std::string fileName);

		///	Finds an asset from the assetMap.
		///		\param fileName : string.
		///		\return requested Resource.
		Resource* GetAsset(std::string fileName);

		/// Opens AAsset for further use.
		///		\param fileName : string name of AAsset.
		///		\return pointer to AAsset.
		AAsset* OpenAAsset(std::string fileName);

		/// Returns content of AAsset as character.
		///		\param asset : pointer of AAsset.
		///		\return content of AAsset as vector<char>.
		std::vector<char> ReadChar(AAsset* asset);

		/// Returns content of AAsset as unsigned character.
		///		\param asset : pointer of AAsset.
		///		\return content of AAsset as vector<unsigned char>.
		std::vector<unsigned char> ReadUnsignedChar(AAsset* asset);

		/// Checks if AAssetManager has been set before class use.
		///		\return bool depending on success.
		bool ManagerCheck();

		/// Constructor as private class.
		ResourceManager() : manager(nullptr) {};

		static ResourceManager* instance; ///< Pointer to only instance of the class.
		AAssetManager* manager; ///< Pointer to Androids AAssetManager.

		//Typedef to ease coding
		typedef std::map<std::string, Resource*> assetMap;
		assetMap assets;


	protected: // These are handled in Application calls.

		/// Initializes AAssetManager location for ResourceManager.
		///		\param manager : AAssetManager pointer.
		void Initialize(AAssetManager* manager);

		/// Deletes ResourceManager instance.
		/// Should be called once application is ready to close.
		void DestroyInstance();

		/// Deletes an asset from the assetMap.
		///		\param filename : name of the file to be deleted.
		void DeleteResource(std::string filename);

		/// Destructor.
		virtual ~ResourceManager();

	};
}

#endif // !RESOURCEMANAGER_H