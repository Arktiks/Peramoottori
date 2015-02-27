#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <android\asset_manager.h>
#include <resources\Image.h>
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>

enum ASSET_TYPE
{
	IMAGE = 1,
	TEXTURE = 2,
	SOUND = 3,
	FONT = 4,
};

namespace pm
{
	class ResourceManager
	{
	public:
		//ResourceManager();
		//ResourceManager() : manager(nullptr){};
		static ResourceManager* GetInstance(AAssetManager* manager = nullptr);

		void Initialize(AAssetManager* manager);

		void DestroyInstance();


		std::string ReadText(std::string fileName);



		Image ReadImage(std::string fileName);

		AAsset* GetAsset(std::string fileName);

		virtual ~ResourceManager() {};
		ResourceManager() : manager(nullptr) {};

		std::string ReadAsset(std::string filePath);

	private:


		bool ManagerCheck();

		AAsset* OpenAsset(std::string fileName);

		std::vector<char> ReadChar(AAsset* asset);

		std::vector<unsigned char> ReadUnsignedChar(AAsset* asset);



		static ResourceManager* instance; ///< Pointer to only instance of the class.
		AAssetManager* manager; ///< Pointer to Androids AAssetManager.




		std::multimap <std::string, int> assets;
	};
}
#endif // !RESOURCEMANAGER_H