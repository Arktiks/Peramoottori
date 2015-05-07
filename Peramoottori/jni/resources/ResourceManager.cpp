#include "ResourceManager.h"
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>

#include <resources\TextResource.h>
#include <resources\ImageResource.h>
#include <resources\FontResource.h>
#include <resources\AudioResource.h>

pm::ResourceManager* pm::ResourceManager::instance = nullptr;

const std::string TXT = ".txt";
const std::string TTF = ".ttf";
const std::string OGG = ".ogg";
const std::string PNG = ".png";

/// User Functions ///

///TODO tää toimii nyt sillai typerästi että loadAsset palauttaa käyttäjälle Resourcen,
///millö käyttäjä ei nyt juuri voi tehdä mitään. Pitää siis tehdä jotenkin sillai, 
///että kun tietyn tyyppinen resurssi luodaan, niin itse Resource luokasta pääsee 
///assettien dataan käsiksi joita käyttäjä pystyy hyödyntämään.

pm::ResourceManager* pm::ResourceManager::GetInstance()
{
	if (instance == nullptr) // If instance has not been initialized yet.
		instance = NEW ResourceManager;
	return instance;
}

pm::Resource* pm::ResourceManager::LoadAsset(std::string fileName)
{
	assetMap::iterator check = assets.find(fileName); // Iterate through loaded Resources.

	if (check == assets.end()) // Checking that there isn't a file with the same name as the parameter in assetMap.
	{
		std::string tempFileExtension = fileName.substr(fileName.size() - 4); // Extension of file.

		if (tempFileExtension.compare(TXT) == 0) // TXT FILE
		{
			std::string textData = ReadText(fileName);
			TextResource* tempTextData = NEW TextResource(textData);
			assets.insert(std::pair<std::string, Resource*>(fileName, tempTextData));

			return tempTextData; // Return created resource instantly.
		}

		else if (tempFileExtension.compare(TTF) == 0) // TTF FILE
		{
			AAsset* ttfAsset = OpenAAsset(fileName);
			std::vector<FT_Byte> ttf = ReadUnsignedChar(ttfAsset);
			//AAsset_close(ttfAsset);
		
			FontResource* tempFontData = NEW FontResource(ttf);
			assets.insert(std::pair<std::string, Resource*>(fileName, tempFontData));

				AAsset_close(ttfAsset);

				return tempFontData; // Return created resource instantly.
		}

		else if (tempFileExtension.compare(OGG) == 0) // OGG FILE
		{
			AAsset *tempAudioAsset = ReadAudio(fileName);
			off_t start, length;

			int	tempFileDescriptor = AAsset_openFileDescriptor(tempAudioAsset, &start, &length);
			AudioResource* tempAudioResource = NEW AudioResource(tempFileDescriptor, length, start);
			assets.insert(std::pair<std::string, Resource*>(fileName, tempAudioResource));

			AAsset_close(tempAudioAsset);

			return tempAudioResource;

		}

		else if (tempFileExtension.compare(PNG) == 0) // PNG FILE
		{
			ImageResource* tempImageResource = NEW ImageResource(ReadImage(fileName));
			assets.insert(std::pair<std::string, Resource*>(fileName, tempImageResource));

			return tempImageResource;
		}

		else
		{
			DEBUG_WARNING(("ResourceManager could not recognize (%s) filetype!", fileName.c_str()));
			return nullptr;
		}
	}

	else // If there is a file with the same name already.
	{
		DEBUG_INFO(("(%s) has already been loaded.", fileName.c_str()));
		return GetAsset(fileName);
	}
}

void pm::ResourceManager::ClearAssetMap()
{
	assets.clear();
}

/// Private Functions ///

std::string pm::ResourceManager::ReadText(std::string fileName)
{
	AAsset* tempAsset = OpenAAsset(fileName);
	
	if (tempAsset != nullptr)
	{
		std::vector<char> tempBuffer = ReadChar(tempAsset); // Buffer containing text content.
		std::string tempString(tempBuffer.begin(), tempBuffer.end()); // Create string from buffer.
		AAsset_close(tempAsset);
		//DEBUG_INFO((tempString.c_str())); // Prints processed text as confirmation.

		return tempString;
	}
	else
		AAsset_close(tempAsset);
		return std::string(); // Returns empty string if there is an error.
}

//SIIRRÄ FONTIN LATAUS TÄNNE
//std::string pm::ResourceManager::ReadFont(std::string fileName)
//{
//	AAsset* tempAsset = OpenAAsset(fileName);
//
//	if (tempAsset)
//	{
//		std::vector<char> tempBuffer = ReadChar(tempAsset); // Buffer containing text content.
//		std::string tempString(tempBuffer.begin(), tempBuffer.end()); // Create string from buffer.
//		DEBUG_INFO((tempString.c_str())); // Prints processed text as confirmation.
//		return tempString;
//	}
//	else
//		return std::string();
//
//}

AAsset* pm::ResourceManager::ReadAudio(std::string fileName)
{
	return OpenAAsset(fileName);
}

/// FIX THIS TO BE IN THE SAME FORM AS OTHER RESOURCE LOADERS
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
		AAsset_close(tempAsset);
		return tempBuffer;
	}
	else
		AAsset_close(tempAsset);
		return tempBuffer; // Returns empty Image if there is an error.
}

pm::Resource* pm::ResourceManager::GetAsset(std::string fileName)
{
	assetMap::iterator it = assets.find(fileName); // Iterate through loaded Resources.

	if (it == assets.end()) // Couldn't find Resource.
	{
		DEBUG_WARNING(("ResourceManger couldn't find Resource %s!", fileName.c_str()));
		return nullptr;
		//DEBUG_INFO(("File was already in memory"));
		//return new Resource;
	}
	else
		return it->second; // Found a match.
}

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
				DEBUG_INFO(("Reading file failed: %s, filelength zero", fileName.c_str()));
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

bool pm::ResourceManager::ManagerCheck()
{
	if (manager != nullptr) // If manager has been set everything is fine.
		return true;
	else
	{
		DEBUG_WARNING(("Trying to use ResourceManager without initializing!"));
		return false;
	}
}

/// Engine Functions ///

void pm::ResourceManager::Initialize(AAssetManager* manager)
{
	if ((this->manager) != nullptr)  // If manager has already been set write a warning.
	{
		DEBUG_WARNING(("ResourceManager has already been initialized!"));
		//ASSERT(false);
	}

	(this->manager) = manager;
}

void pm::ResourceManager::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}

void pm::ResourceManager::DeleteResource(std::string fileName)
{
	assetMap::iterator it = assets.find(fileName); // Iterate through loaded Resources.

	if (it == assets.end()) // Couldn't find Resource.
	{
		DEBUG_WARNING(("Couldn't find Resource %s!", fileName.c_str()));
	}
	else
		delete it->second; // Found a match.
}

pm::ResourceManager::~ResourceManager()
{	
}