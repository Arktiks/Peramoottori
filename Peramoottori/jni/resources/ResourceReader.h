#ifndef RESOURCEREADER_H
#define RESOURCEREADER_H

#include <android\asset_manager.h>
#include <structs\LoadedImage.h>
#include <string>
#include <vector>

class ResourceReader
{
public:

	static ResourceReader* GetInstance(AAssetManager* manager = nullptr);
	void Initialize(AAssetManager* manager);
	void DestroyInstance();
	
	std::string String(std::string fileName);
	LoadedImage PNG(std::string fileName);

	virtual ~ResourceReader() {};

private:

	bool ManagerCheck();
	AAsset* OpenAsset(std::string fileName);
	std::vector<char> ReadAsset(AAsset* asset);
	
	ResourceReader() : manager(nullptr) {};

	static ResourceReader* instance;
	AAssetManager* manager;
};

#endif