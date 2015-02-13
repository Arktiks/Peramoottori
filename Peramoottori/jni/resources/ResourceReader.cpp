#include "ResourceReader.h"
#include <system\PMdebug.h>
#include <system\PMassert.h>
#include <lodepng.h>

ResourceReader* ResourceReader::instance = nullptr;

ResourceReader* ResourceReader::GetInstance(AAssetManager* manager)
{
	if (instance == nullptr) // Initialize instance.
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
	if (manager != nullptr)
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

std::string ResourceReader::String(std::string fileName)
{
	AAsset* tempAsset = OpenAsset(fileName);

	if (tempAsset)
	{
		std::vector<char> tempBuffer = ReadAsset(tempAsset);

		std::string tempString(tempBuffer.begin(), tempBuffer.end()); // Create string from buffer.
		PMdebug::MsgInfo(tempString.c_str()); // Prints processed text.
		return tempString;
	}
	else
		return std::string(); // Returns empty string if there is an error.
}

LoadedImage ResourceReader::PNG(std::string fileName)
{
	AAsset* tempAsset = OpenAsset(fileName);

	if (tempAsset)
	{
		std::vector<unsigned char> decodedImage; // Will contain the decoded PNG.
		std::vector<char> assetBuffer = ReadAsset(tempAsset); // Received signed char vector.
		std::vector<unsigned char> tempBuffer; // TEE KONVERSIO

		//TODO: Castaa assetBuffer unsigned.

		unsigned int width, height; // Make note of image dimensions.
		unsigned int error = lodepng::decode(tempBuffer, width, height, decodedImage); // Decode the raw data.
		
		if (error) // Warn about errors.
			PMdebug::MsgWarning("PNG decoder error ", error, ": ", lodepng_error_text(error), " (", fileName.c_str(), ")");
		
		return LoadedImage(decodedImage, width, height);
	}
	else
		return LoadedImage();
}

bool ResourceReader::ManagerCheck()
{
	if (instance->manager != nullptr)
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
		AAsset* tempAsset = AAssetManager_open(manager, fileName.c_str(), AASSET_MODE_UNKNOWN); // Open asset using manager.
		size_t tempSize = AAsset_getLength(tempAsset); // Check asset length.

		if (tempAsset != nullptr && tempSize > 0) // Asset opened succesfully and size greater than 0.
		{
			PMdebug::MsgInfo("Succesfully read file: ", fileName.c_str(), " (", tempSize, ")");
			return tempAsset; // Return asset pointer for further use.
		}
		else
		{
			PMdebug::MsgWarning("Reading file failed: ", fileName.c_str());
			return nullptr;
		}
	}
}

std::vector<char> ResourceReader::ReadAsset(AAsset* asset)
{
	size_t tempSize = AAsset_getLength(asset); // Count length of asset.
	std::vector<char> tempBuffer; // Buffer for asset content.
	tempBuffer.resize(tempSize); // Reserver space for content.

	AAsset_read(asset, &tempBuffer[0], tempSize); // Assign content into buffer.
	AAsset_close(asset); // Destroy asset, no delete neccessary.
}