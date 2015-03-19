#include "ResourceManager.h"
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>

using namespace pm;
ResourceManager* ResourceManager::instance;

void ResourceManager::ReadAsset(std::string fileName)
{
	int tempLen = fileName.length();

	std::string tempFileExtension = fileName.substr(fileName.size() - 4);
	//tempFileExtension.c_str();

	std::string tempTxt = ".txt";
	std::string tempTtf = ".ttf";
	std::string tempOgg = ".ogg";
	std::string tempPng = ".png";

	if (strcmp(tempFileExtension.c_str(),tempTxt.c_str())==0)
	{
		DEBUG_INFO(("TXT compare works"));

		resource.SetName(fileName);

		std::string textData = ReadText(resource.GetName());

		TextResource* tempTextData = NEW TextResource(textData);

		assets.insert(std::make_pair<std::string, Resource*>(resource.GetName(), tempTextData));

	}

	else if (strcmp(tempFileExtension.c_str(), tempTtf.c_str())==0)
	{
		DEBUG_INFO(("TTF compare works"));
		//ReadFont
	}

	else if (strcmp(tempFileExtension.c_str(), tempOgg.c_str())==0)
	{
		DEBUG_INFO(("OGG compare works"));
		//ReadSound
	}

	else if (strcmp(tempFileExtension.c_str(), tempPng.c_str())==0)
	{
		DEBUG_INFO(("PNG compare works"));
		ImageResource* tempImageResource = NEW ImageResource(ReadImage(fileName));

		assets.insert(std::make_pair<std::string, Resource*>(resource.GetName(), tempImageResource));
	}

	else
	{
		DEBUG_WARNING(("File type not recognized"));
	}
}

ResourceManager* ResourceManager::GetInstance(AAssetManager* manager)
{
	if (instance == nullptr) // If instance has not been initialized yet.
	{
		instance = new ResourceManager;
		instance->Initialize(manager);
	}
	else if (instance != nullptr && instance->manager == nullptr) // If instance has been initialize and manager not.
	{
		instance->Initialize(manager);
	}
	return instance;
}

void ResourceManager::Initialize(AAssetManager* manager)
{
	if (manager != nullptr)  // If manager has already been set write a warning.
		DEBUG_WARNING(("ResourceManager has already been initialized!"));
	else
		DEBUG_INFO(("ResourceManager assigned"));

	(this->manager) = manager;
}

void ResourceManager::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}

std::string ResourceManager::ReadText(std::string fileName)
{
	AAsset* tempAsset = OpenAsset(fileName);

	if (tempAsset)
	{
		std::vector<char> tempBuffer = ReadChar(tempAsset); // Buffer containing text content.
		std::string tempString(tempBuffer.begin(), tempBuffer.end()); // Create string from buffer.
		DEBUG_INFO((tempString.c_str())); // Prints processed text as confirmation.
		return tempString;
	}
	else
		return std::string(); // Returns empty string if there is an error.
}

std::vector<unsigned char> ResourceManager::ReadImage(std::string fileName)
{
	AAsset* tempAsset = OpenAsset(fileName);
	std::vector<unsigned char> tempBuffer;

	if (tempAsset)
	{
		tempBuffer = ReadUnsignedChar(tempAsset); 
		return tempBuffer;
	}
	else
		return tempBuffer; // Returns empty Image if there is an error.
}

AAsset* ResourceManager::GetAsset(std::string fileName)
{
	// Temporary function for audio streaming.
	// The AAsset needs to be closed manually.
	return OpenAsset(fileName);
}

bool ResourceManager::ManagerCheck()
{
	if (instance->manager != nullptr) // If manager has been set everything is fine.
		return true;
	else
	{
		DEBUG_WARNING(("Trying to use ResourceManager without initializing!"));
		return false;
	}
}

AAsset* ResourceManager::OpenAsset(std::string fileName)
{
	if (ManagerCheck())
	{
		AAsset* tempAsset = AAssetManager_open(manager, fileName.c_str(), AASSET_MODE_UNKNOWN); // Open AAsset using AAssetManager.

		if (tempAsset != nullptr) // AAsset opened succesfully and size greater than 0.
		{
			size_t tempSize = AAsset_getLength(tempAsset); // Check AAsset length.
			if (tempSize > 0)
			{
				DEBUG_INFO(("Succesfully read file: %s (%i)", fileName.c_str(), tempSize));
				return tempAsset; // Return AAsset pointer for further use.
			}
			else
			{
				DEBUG_INFO(("Reading file failed: %s, filelenght zero", fileName.c_str()));
			}
		}
		else // There was an error opening the AAsset.
		{
			DEBUG_WARNING(("Reading file failed: %s", fileName.c_str()));
			return nullptr;
		}
	}
	return nullptr;
}

std::vector<char> ResourceManager::ReadChar(AAsset* asset)
{
	size_t tempSize = AAsset_getLength(asset);		// Check AAsset length.
	std::vector<char> tempBuffer;					// Buffer for AAsset content.
	tempBuffer.resize(tempSize);					// Reserver space for content.
	AAsset_read(asset, &tempBuffer[0], tempSize);	// Assign content into buffer.
	AAsset_close(asset);							// Destroy opened AAsset, no delete neccessary.
	return tempBuffer;
}

std::vector<unsigned char> ResourceManager::ReadUnsignedChar(AAsset* asset)
{
	size_t tempSize = AAsset_getLength(asset);
	std::vector<unsigned char> tempBuffer;
	tempBuffer.resize(tempSize);
	AAsset_read(asset, &tempBuffer[0], tempSize);
	AAsset_close(asset);
	return tempBuffer;
}