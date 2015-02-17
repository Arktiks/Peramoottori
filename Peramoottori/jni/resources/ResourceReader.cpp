#include "ResourceReader.h"
#include <system\PMdebug.h>
#include <system\PMassert.h>

using namespace pm;
ResourceReader* ResourceReader::instance = nullptr;

ResourceReader* ResourceReader::GetInstance(AAssetManager* manager)
{
	if (instance == nullptr) // If instance has not been initialized yet.
	{
		instance = new ResourceReader;
		instance->Initialize(manager);
	}
	else if (instance != nullptr && instance->manager == nullptr) // If instance has been initialize and manager not.
	{
		instance->Initialize(manager);
	}
	return instance;
}

void ResourceReader::Initialize(AAssetManager* manager)
{
	if (manager != nullptr) // If manager has already been set write a warning.
		PMdebug::MsgWarning("ResourceReader manager has already been initialized!");
	else
		PMdebug::MsgInfo("ResourceReader manager assigned.");

	(this->manager) = manager;
}

void ResourceReader::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}

std::string ResourceReader::ReadText(std::string fileName)
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

Image ResourceReader::ReadImage(std::string fileName)
{
	AAsset* tempAsset = OpenAsset(fileName);

	if(tempAsset)
	{
		std::vector<unsigned char> tempBuffer = ReadUnsignedChar(tempAsset); // Buffer containing image content.
		std::string tempString(tempBuffer.begin(), tempBuffer.end()); // Create string from buffer.
		// Currently returned Image doesn't have picture dimensions.
		return Image(tempString);
	}
	else
		return Image(); // Returns empty Image if there is an error.
}

AAsset* ResourceReader::GetAsset(std::string fileName)
{
	// Temporary function for audio streaming.
	// The AAsset needs to be closed manually.
	return OpenAsset(fileName);
}

bool ResourceReader::ManagerCheck()
{
	if (instance->manager != nullptr) // If manager has been set everything is fine.
		return true;
	else
	{
		PMdebug::MsgWarning("Trying to use ResourceReader without initializing!");
		return false;
	}
}

AAsset* ResourceReader::OpenAsset(std::string fileName)
{
	if (ManagerCheck())
	{
		AAsset* tempAsset = AAssetManager_open(manager, fileName.c_str(), AASSET_MODE_UNKNOWN); // Open AAsset using AAssetManager.
		size_t tempSize = AAsset_getLength(tempAsset); // Check AAsset length.

		if (tempAsset != nullptr && tempSize > 0) // AAsset opened succesfully and size greater than 0.
		{
			PMdebug::MsgInfo("Succesfully read file: %s (%i)", fileName.c_str(), tempSize);
			return tempAsset; // Return AAsset pointer for further use.
		}
		else // There was an error opening the AAsset.
		{
			PMdebug::MsgWarning("Reading file failed: %s", fileName.c_str());
			return nullptr;
		}
	}
}

std::vector<char> ResourceReader::ReadChar(AAsset* asset)
{
	size_t tempSize = AAsset_getLength(asset);		// Check AAsset length.
	std::vector<char> tempBuffer;					// Buffer for AAsset content.
	tempBuffer.resize(tempSize);					// Reserver space for content.
	AAsset_read(asset, &tempBuffer[0], tempSize);	// Assign content into buffer.
	AAsset_close(asset);							// Destroy opened AAsset, no delete neccessary.
	return tempBuffer;
}

std::vector<unsigned char> ResourceReader::ReadUnsignedChar(AAsset* asset)
{
	size_t tempSize = AAsset_getLength(asset);
	std::vector<unsigned char> tempBuffer;
	tempBuffer.resize(tempSize);
	AAsset_read(asset, &tempBuffer[0], tempSize);
	AAsset_close(asset);
	return tempBuffer;
}