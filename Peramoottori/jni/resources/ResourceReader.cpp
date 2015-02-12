#include "ResourceReader.h"
#include <lodepng.h>
#include <vector>

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

void ResourceReader::Initialize(AAssetManager* manager)
{
	if (instance->manager == nullptr)
		// Warning that manager has already been assigned.
		;
	instance->manager = manager;
}

void ResourceReader::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}

std::string ResourceReader::String(std::string fileName)
{
	AAsset* tempAsset = OpenAsset(fileName);

	if (tempAsset)
	{
		size_t tempSize = AAsset_getLength(tempAsset); // Count length of file.
		std::vector<char> tempBuffer; // Use vector<char> from the start instead of char*.
		tempBuffer.resize(tempSize); // Reserver space for content.

		AAsset_read(tempAsset, &tempBuffer[0], tempSize); // Assign content into buffer.
		AAsset_close(tempAsset); // Destroy asset, no delete neccessary.

		std::string tempString(tempBuffer.begin(), tempBuffer.end()); // Create string from buffer.
		return tempString;
	}
	else
	{
		// Error log.
		return std::string();
	}
}

LoadedImage ResourceReader::PNG(std::string fileName)
{
	AAsset* tempAsset = OpenAsset(fileName);

	if (tempAsset)
	{
		std::vector<unsigned char> tempBuffer;
		std::vector<unsigned char> decodedImage; // Will contain the decoded PNG.

		size_t tempSize = AAsset_getLength(tempAsset);
		tempBuffer.resize(tempSize);

		AAsset_read(tempAsset, &tempBuffer[0], tempSize);
		AAsset_close(tempAsset);

		unsigned int width, height; // Make note of image dimensions.
		unsigned error = lodepng::decode(tempBuffer, width, height, decodedImage);


	}
	else
	{
		// Error log.
		//return;
	}
}

bool ResourceReader::ManagerCheck()
{
	return true;
	// Check if manager has been assigned before usage.
	// Add debug.
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

/* Marked to be removed.
char* tempBuffer = (char*)malloc(sizeof(char) * tempSize + 1); // Allocate memory for temporary buffer.
AAsset_read(tempAsset, tempBuffer, tempSize); // Assign content into buffer.
tempBuffer[tempSize] = '\0'; // Prevent errors.
delete tempBuffer;
tempString.assign(tempBuffer, tempSize); // Assign content into string. */