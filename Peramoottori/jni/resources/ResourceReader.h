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
		/// Returns instance of ResourceReader.
		/// Only one instance of ResourceReader will exist during runtime.
		static ResourceReader* GetInstance(AAssetManager* manager = nullptr);

		/// Initializes AAssetManager location for ResourceReader.
		///		\param manager : AAssetManager pointer, defaults to nullptr.
		void Initialize(AAssetManager* manager);

		/// Deletes ResourceReader instance.
		/// Needs to be called once application is ready to close.
		void DestroyInstance();

		/// Returns content of asset as std::string.
		///		\param fileName : string name of asset.
		///		\return content of asset.
		std::string ReadText(std::string fileName);

		/// Returns image that contains pixel data and dimensions.
		/// Picture asset is contained as unsigned char.
		///		\parama fileName : string name of asset.
		///		\return content of asset.
		Image ReadImage(std::string fileName);

		/// Destructor.
		virtual ~ResourceReader() {};

		// For later use.
		//std::vector<signed char> ReadAudio(std::string fileName);

	private:
		/// Checks if AAssetManager has been set before class use.
		/**
			\return bool depending on success.
		*/
		bool ManagerCheck();

		///
		/**
		*
		*/
		AAsset* OpenAsset(std::string fileName);

		/////////////////////////////////////////////////
		/// asd
		/////////////////////////////////////////////////



		///
		/**
		*
		*/
		std::vector<char> ReadChar(AAsset* asset);

		///
		/**
		*
		*/
		std::vector<unsigned char> ReadUnsignedChar(AAsset* asset);

		///
		/**
		*
		*/
		ResourceReader() : manager(nullptr) {};

		static ResourceReader* instance; ///<
		AAssetManager* manager; ///<
	};
}

#endif