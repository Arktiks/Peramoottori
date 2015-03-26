#include "ResourceManager.h"
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>

pm::ResourceManager* pm::ResourceManager::instance;
ResourceManager* ResourceManager::instance = nullptr;


/// User Functions ///

ResourceManager* ResourceManager::GetInstance()
{
	if (instance == nullptr) // If instance has not been initialized yet.
		instance = new ResourceManager;

	return instance;
}

pm::Resource pm::ResourceManager::LoadAsset(std::string fileName)
{
	assetMap::iterator check = assets.find(fileName);

	// Checking that there isn't a file with the same name as the parameter in the assetMap
	if (check == assets.end())
	{
		std::string tempFileExtension = fileName.substr(fileName.size() - 4);
		std::string tempTxt = ".txt";
		std::string tempTtf = ".ttf";
		std::string tempOgg = ".ogg";
		std::string tempPng = ".png";

		// Comparing the extension of text file and tempTxt
		if (strcmp(tempFileExtension.c_str(), tempTxt.c_str()) == 0)
		{
			DEBUG_INFO(("TXT compare works"));

			std::string textData = ReadText(fileName);
			TextResource* tempTextData = NEW TextResource(textData);
			assets.insert(std::make_pair<std::string, Resource*>(fileName, tempTextData));

			return GetAsset(fileName);
		}

		// Comparing the extension of font file and tempTtf
		else if (strcmp(tempFileExtension.c_str(), tempTtf.c_str()) == 0)
		{
			DEBUG_INFO(("TTF compare works"));
			//ReadFont
		}

		// Comparing the extension of audio file and tempOgg
		else if (strcmp(tempFileExtension.c_str(), tempOgg.c_str()) == 0)
		{
			DEBUG_INFO(("OGG compare works"));
			//ReadSound
		}

		// Comparing the extension of image file and tempPng
		else if (strcmp(tempFileExtension.c_str(), tempPng.c_str()) == 0)
		{
			DEBUG_INFO(("PNG compare works"));

			ImageResource* tempImageResource = NEW ImageResource(ReadImage(fileName));
			return GetAsset(fileName);
		}

		else
		{
			DEBUG_WARNING(("File type not recognized"));

			//TODO: FIX THIS ie find a proper return stuff
			return new Resource;
		}
	}

	// If there is a file with the same name already.
	else
	{
		DEBUG_INFO(("File was already in memory"));
		return GetAsset(fileName);
	}
}

std::string pm::ResourceManager::ReadText(std::string fileName)
{
	AAsset* tempAsset = OpenAAsset(fileName);

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

//LOAD FONT FUNCTION HERES()
//{
//}

//LOAD AUDIO FUNCTION HERES()
//TODO FIX THIS TO BE IN THE SAME FORM AS OTHER RESOURCE LOADERS
AAsset* pm::ResourceManager::GetAAsset(std::string fileName)
{
	// Temporary function for audio streaming.
	// The AAsset needs to be closed manually.
	return OpenAAsset(fileName);
}

std::vector<unsigned char> pm::ResourceManager::ReadImage(std::string fileName)
{
	AAsset* tempAsset = OpenAAsset(fileName);
	std::vector<unsigned char> tempBuffer;

	if (tempAsset)
	{
		tempBuffer = ReadUnsignedChar(tempAsset);
		return tempBuffer;
	}
	else
		return tempBuffer; // Returns empty Image if there is an error.
}

pm::Resource pm::ResourceManager::GetAsset(std::string fileName)
{
	assetMap::iterator it = assets.find(fileName);
	if (it == assets.end())
	{
		DEBUG_INFO(("File was already in memory"));
		return new Resource;
	}
	else
	{
		Resource *tempResource = it->second;
		return *tempResource;
	}
}

pm::ResourceManager* pm::ResourceManager::GetInstance(AAssetManager* manager)
{
	// Temporary function for audio streaming.
	// The AAsset needs to be closed manually.
	return OpenAsset(fileName);
void pm::ResourceManager::Initialize(AAssetManager* manager)
void pm::ResourceManager::DestroyInstance()
}

bool pm::ResourceManager::ManagerCheck()
{
AAsset* pm::ResourceManager::OpenAAsset(std::string fileName)
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

std::vector<char> pm::ResourceManager::ReadChar(AAsset* asset)
{
	size_t tempSize = AAsset_getLength(asset);		// Check AAsset length.
	std::vector<char> tempBuffer;					// Buffer for AAsset content.
	tempBuffer.resize(tempSize);					// Reserver space for content.
	AAsset_read(asset, &tempBuffer[0], tempSize);	// Assign content into buffer.
	AAsset_close(asset);							// Destroy opened AAsset, no delete neccessary.
	return tempBuffer;
}

std::vector<unsigned char> pm::ResourceManager::ReadUnsignedChar(AAsset* asset)
{
	size_t tempSize = AAsset_getLength(asset);
	std::vector<unsigned char> tempBuffer;
	tempBuffer.resize(tempSize);
	AAsset_read(asset, &tempBuffer[0], tempSize);
	AAsset_close(asset);
	return tempBuffer;
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


/// Engine Functions ///

void ResourceManager::Initialize(AAssetManager* manager)
{
	if (manager != nullptr)  // If manager has already been set write a warning.
	{
		DEBUG_WARNING(("ResourceManager has already been initialized!"));
		ASSERT(false);
	}
	else
		DEBUG_INFO(("ResourceManager assigned!"));

	(this->manager) = manager;
}

void ResourceManager::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}

ResourceManager::~ResourceManager()
{
	// CLEAN UP ASSETS
}