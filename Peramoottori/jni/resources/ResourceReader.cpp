#include "ResourceReader.h"
#include <lodepng.h>

ResourceReader* ResourceReader::instance = nullptr;
AAssetManager* ResourceReader::manager = nullptr;

ResourceReader* ResourceReader::GetInstance(AAssetManager* manager)
{
	if (instance == nullptr)
	{
		instance = new ResourceReader;
		instance->manager = manager;
	}
	else if (instance != nullptr && manager == nullptr)
	{
		instance->manager = manager;
	}
	return instance;
}

void ResourceReader::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}

char* ResourceReader::Character(std::string fileName)
{
	AAsset* tempAsset = OpenAsset(fileName);

	if (tempAsset)
	{
		size_t tempSize = AAsset_getLength(tempAsset);
		char* tempBuffer = (char*)malloc(sizeof(char) * tempSize + 1);
		AAsset_read(tempAsset, tempBuffer, tempSize);
		tempBuffer[tempSize] = '\0';
		
		AAsset_close(tempAsset); // Tuhoaa tempAssetin sisällön, ei tarvitse deleteä.
		return tempBuffer;
	}
	else
	{
		// Virhelogia.
		return nullptr;
	}
}

std::string ResourceReader::String(std::string fileName)
{
	AAsset* tempAsset = OpenAsset(fileName);

	if (tempAsset)
	{
		size_t tempSize = AAsset_getLength(tempAsset);
		char* tempBuffer = (char*)malloc(sizeof(char) * tempSize + 1);
		AAsset_read(tempAsset, tempBuffer, tempSize);
		tempBuffer[tempSize] = '\0';

		AAsset_close(tempAsset); // Tuhoaa tempAssetin sisällön, ei tarvitse deleteä.
		return tempBuffer;
	}
	else
	{
		// Virhelogia.
		return nullptr;
	}
}

LoadedImage* ResourceReader::Picture(std::string fileName)
{
	AAsset* asset = AAssetManager_open(manager, fileName.c_str(), AASSET_MODE_UNKNOWN);

	//http://www.learnopengles.com/loading-a-png-into-memory-and-displaying-it-as-a-texture-with-opengl-es-2-using-almost-the-same-code-on-ios-android-and-emscripten/
	// Kokeilla ensin LodePNG saada toimimaan, muuten pitää ehkä lukea binääristä tai jotain.
}

bool ResourceReader::ManagerCheck()
{
	return true;
	// Tarkistaa että manager on asetettu ennen latauskutsuja.
	// Tulee käyttämään Debuggia kunhan se on valmis.
}

AAsset* ResourceReader::OpenAsset(std::string fileName)
{
	if (ManagerCheck())
	{
		AAsset* tempAsset = AAssetManager_open(manager, fileName.c_str(), AASSET_MODE_UNKNOWN);
		if (tempAsset != nullptr)
		{
			//LOGI("Luettu tiedosto %s (%d).", fileName.c_str(), size);
			//LOGI("%s", buffer);
			return tempAsset;
		}
		else
		{
			//LOGW("Tiedoston %s lukeminen ei onnistunut.", fileName.c_str());
			return nullptr;
		}
	}
}