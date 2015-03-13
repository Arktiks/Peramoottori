#include "ResourceManager.h"
#include <System\PMassert.h>
#include <System\PMdebug.h>

using namespace pm;
ResourceManager* ResourceManager::instance;

void ResourceManager::ReadAsset(std::string filePath)
{
	int tempLen = filePath.length();

	filePath.substr(filePath.size() - 4);

	std::string tempTxt = ".txt";
	std::string tempTtf = ".ttf";
	std::string tempOgg = ".ogg";
	std::string tempPng = ".png";

	if (filePath.compare(tempTxt.c_str()))
	{
		PMdebug::MsgInfo("TXT compare works");
	}

	else if (filePath.compare(tempTtf.c_str()))
	{
		PMdebug::MsgInfo("TTF compare works");
	}

	else if (filePath.compare(tempOgg.c_str()))
	{
		PMdebug::MsgInfo("OGG compare works");
	}

	else if (filePath.compare(tempPng.c_str()))
	{
		PMdebug::MsgInfo("PNG compare works");
	}

	else
	{
		PMdebug::MsgWarning("File type not recognized");
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
		PMdebug::MsgWarning("ResourceManager has already been initialized!");
	else
		PMdebug::MsgInfo("ResourceManager assigned");

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
		PMdebug::MsgInfo(tempString.c_str()); // Prints processed text as confirmation.
		return tempString;
	}
	else
		return std::string(); // Returns empty string if there is an error.
}

Image ResourceManager::ReadImage(std::string fileName)
{
	AAsset* tempAsset = OpenAsset(fileName);

	if (tempAsset)
	{
		std::vector<unsigned char> tempBuffer = ReadUnsignedChar(tempAsset); // Buffer containing picture content.
		//std::string tempString(tempBuffer.begin(), tempBuffer.end()); // Create string from buffer.
		// Currently Images picture dimensions are not calculated.
		// Image dimensions can be decoded in Graphics module.
		return Image(tempBuffer);
	}
	else
		return Image(); // Returns empty Image if there is an error.
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
		PMdebug::MsgWarning("Trying to use ResourceManager without initializing!");
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
				PMdebug::MsgInfo("Succesfully read file: %s (%i)", fileName.c_str(), tempSize);
				return tempAsset; // Return AAsset pointer for further use.
			}
			else
			{
				PMdebug::MsgWarning("Reading file failed: %s, filelenght zero", fileName.c_str());
			}
		}
		else // There was an error opening the AAsset.
		{
			PMdebug::MsgWarning("Reading file failed: %s", fileName.c_str());
			return nullptr;
		}
	}
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