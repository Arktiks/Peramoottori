#ifndef RESOURCEREADER_H
#define RESOURCEREADER_H

#include <android\asset_manager.h>
#include <structs\LoadedImage.h>
#include <resources\Image.h>
#include <string>
#include <vector>

namespace pm
{
	/// Reads resources using android AAssetManager.
	/// Singleton class that purely focuses on reading assets and not storing them.

	class ResourceReader
	{
	public:
		/// Static function that returns instance pointer of ResourceReader.
		/// Only one instance of ResourceReader will exist during runtime.
		///		\param manager : AAssetManager pointer, defaults to nullptr.
		///		\return pointer to only instance of this class.
		static ResourceReader* GetInstance(AAssetManager* manager = nullptr);

		/// Initializes AAssetManager location for ResourceReader.
		///		\param manager : AAssetManager pointer.
		void Initialize(AAssetManager* manager);

		/// Deletes ResourceReader instance.
		/// Should be called once application is ready to close.
		void DestroyInstance();

		/// Returns content of AAsset as std::string.
		///		\param fileName : string name of AAsset.
		///		\return content of AAsset as string.
		std::string ReadText(std::string fileName);

		/// Returns image that contains pixel data.
		/// Image is contained as unsigned char.
		///		\parama fileName : string name of AAsset.
		///		\return content of AAsset as Image.
		Image ReadImage(std::string fileName);

		/// Returns opened AAsset for further use.
		/// The AAsset needs to be closed manually.
		///		\parama fileName : string name of AAsset.
		///		\return pointer to AAsset.
		AAsset* GetAsset(std::string fileName);

		/// Destructor.
		virtual ~ResourceReader() {};

	private:
		/// Checks if AAssetManager has been set before class use.
		///		\return bool depending on success.
		bool ManagerCheck();

		/// Opens AAsset for further use.
		///		\param fileName : string name of AAsset.
		///		\return pointer to AAsset.
		AAsset* OpenAsset(std::string fileName);

		/// Returns content of AAsset as character.
		///		\param asset : pointer of AAsset.
		///		\return content of AAsset as vector<char>.
		std::vector<char> ReadChar(AAsset* asset);

		/// Returns content of AAsset as unsigned character.
		///		\param asset : pointer of AAsset.
		///		\return content of AAsset as vector<unsigned char>.
		std::vector<unsigned char> ReadUnsignedChar(AAsset* asset);

		/// Constructor as private class.
		ResourceReader() : manager(nullptr) {};

		static ResourceReader* instance; ///< Pointer to only instance of the class.
		AAssetManager* manager; ///< Pointer to Androids AAssetManager.
	};
}

#endif

// TO-DO
//std::vector<signed char> ReadAudio(std::string fileName);