#ifndef RESOURCEREADER_H
#define RESOURCEREADER_H

#include <structs\Engine.h>
#include <structs\LoadedImage.h>
#include <string>

/* En saa shared_ptr toimimaan.
#include <tr1\shared_ptr.h>
#include <tr1\memory>
#include <memory>
#include <memory.h> */

class ResourceReader
{
public:
	static ResourceReader* GetInstance(AAssetManager* manager = nullptr);
	static void DestroyInstance();
	virtual ~ResourceReader() {};
	
	char* Text(std::string fileName);
	LoadedImage* Picture(std::string fileName);

private:
	AAsset* OpenAsset(std::string fileName);
	bool ManagerCheck();

	ResourceReader() {};
	static ResourceReader* instance;
	static AAssetManager* manager;
};

#endif