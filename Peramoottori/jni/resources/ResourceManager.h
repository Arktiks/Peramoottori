#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <android\asset_manager.h>
#include <resources\Resource.h>
#include <resources\TextResource.h>
#include <resources\ImageResource.h>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <iostream>

namespace pm
{
	class ResourceManager
	{
	public:		
		
		Resource resource;

		/// This is the main resource management function for the user.
		/// Checks that there won't be duplicate files.
		/// Determines the type of the file and calls the proper function to decrypt it.
		/// Every file is converted to a Resource type.
		/// Pushes Resource to the assetMap with the file name as it's key.
		///		\param fileName : string name of the file.
		///		\return Resource from assetMap.
		Resource LoadAsset(std::string fileName);

		/// Static function that returns instance pointer of ResourceManager.
		/// Only one instance of ResourceManager will exist during runtime.
		///		\param manager : AAssetManager pointer, defaults to nullptr.
		///		\return pointer to only instance of this class.
		static ResourceManager* GetInstance(AAssetManager* manager = nullptr);

		/// Initializes AAssetManager location for ResourceManager.
		///		\param manager : AAssetManager pointer.
		void Initialize(AAssetManager* manager);

		/// Deletes ResourceManager instance.
		/// Should be called once application is ready to close.
		void DestroyInstance();

		/// Returns content of AAsset as std::string.
		///		\param fileName : string name of AAsset.
		///		\return content of AAsset as string.
		std::string ReadText(std::string fileName);

		/// Returns vector that contains pixel data.
		/// Image is contained as unsigned char vector.
		///		\param fileName : string name of AAsset.
		///		\return content of AAsset as unsigned char vector.
		std::vector<unsigned char> ReadImage(std::string fileName);

		/// Returns opened AAsset for further use.
		/// The AAsset needs to be closed manually.
		///		\parama fileName : string name of AAsset.
		///		\return pointer to AAsset.
		AAsset* GetAAsset(std::string fileName);

		/// Destructor.
		virtual ~ResourceManager() {};



	private:
		/// Checks if AAssetManager has been set before class use.
		///		\return bool depending on success.
		bool ManagerCheck();

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

		///	Finds an asset from the assetMap
		///		\param fileName
		///		\return requested resource
		Resource GetAsset(std::string fileName);

		/// Constructor as private class.
		ResourceManager() : manager(nullptr) {};


		static ResourceManager* instance; ///< Pointer to only instance of the class.
		AAssetManager* manager; ///< Pointer to Androids AAssetManager.

		//Typedef to ease coding
		typedef std::map<std::string, Resource*> assetMap;
		assetMap assets;

	};
}
#endif // !RESOURCEMANAGER_H