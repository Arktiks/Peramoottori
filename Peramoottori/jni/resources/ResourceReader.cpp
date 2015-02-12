#include "ResourceReader.h"
#include <system\PMdebug.h>
#include <system\PMassert.h>

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
		PMdebug::MsgInfo("ResourceReader initialized and manager assigned.");
	}
	else if (instance != nullptr && instance->manager == nullptr)
	{
		instance->manager = manager;
		PMdebug::MsgInfo("ResourceReader manager assigned.");
	}
	return instance;
}

void ResourceReader::Initialize(AAssetManager* manager)
{
	if (instance->manager != nullptr)
		PMdebug::MsgWarning("ResourceReader manager has already been initialized.");
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
		PMdebug::MsgInfo(tempString.c_str()); // Prints processed text.
		return tempString;
	}
	else
		return std::string(); // OpenAsset() handles warning messages.
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

/* Marked to be removed.
char* tempBuffer = (char*)malloc(sizeof(char) * tempSize + 1); // Allocate memory for temporary buffer.
AAsset_read(tempAsset, tempBuffer, tempSize); // Assign content into buffer.
tempBuffer[tempSize] = '\0'; // Prevent errors.
delete tempBuffer;
tempString.assign(tempBuffer, tempSize); // Assign content into string. */