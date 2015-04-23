#include "ResourceManager.h"
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>

pm::ResourceManager* pm::ResourceManager::instance = nullptr;

const std::string TXT = ".txt";
const std::string TTF = ".ttf";
const std::string OGG = ".ogg";
const std::string PNG = ".png";

/// User Functions ///

///TODO t‰‰ toimii nyt sillai typer‰sti ett‰ loadAsset palauttaa k‰ytt‰j‰lle Resourcen,
///millˆ k‰ytt‰j‰ ei nyt juuri voi tehd‰ mit‰‰n. Pit‰‰ siis tehd‰ jotenkin sillai, 
///ett‰ kun tietyn tyyppinen resurssi luodaan, niin itse Resource luokasta p‰‰see 
///assettien dataan k‰siksi joita k‰ytt‰j‰ pystyy hyˆdynt‰m‰‰n.

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
			DEBUG_INFO(("Loading TXT file."));

			std::string textData = ReadText(fileName);
			TextResource* tempTextData = NEW TextResource(textData);
			assets.insert(std::pair<std::string, Resource*>(fileName, tempTextData));

			return tempTextData; // Return created resource instantly.
		}

		else if (tempFileExtension.compare(TTF) == 0) // TTF FILE
		{
			DEBUG_INFO(("Loading TTF file."));

			FT_Library  library;
			FT_Face     face;

			int error = FT_Init_FreeType(&library);
			if (error) 
			{
				DEBUG_INFO(("Failed to initialize freetype library"));
			}

			std::vector<FT_Byte> asd = ReadUnsignedChar(OpenAAsset(fileName));

			error = FT_New_Memory_Face(library,
				&asd[0],
				asd.size(),
				0,
				&face);
			if (error == FT_Err_Unknown_File_Format)
			{
				DEBUG_INFO(("The font file could be opened and read, but it appears that its font format is unsupported"));
			}
			else if (error)
			{
				DEBUG_INFO(("Font file could not be opened or read, or it is broken"));
			}
			else
			{
				DEBUG_INFO(("Font loaded"));
				FontResource* tempFontData = NEW FontResource(library, face);
				assets.insert(std::pair<std::string, Resource*>(fileName, tempFontData));

				return tempFontData; // Return created resource instantly.
			}
		}

		else if (tempFileExtension.compare(OGG) == 0) // OGG FILE
		{
			DEBUG_INFO(("Loading OGG file."));
			AAsset* tempAudioAsset = ReadAudio(fileName);
			off_t start, length;

			int	tempFileDescriptor = AAsset_openFileDescriptor(tempAudioAsset, &start, &length);
			AudioResource* tempFileData = NEW AudioResource(tempFileDescriptor, tempAudioAsset);
			assets.insert(std::pair<std::string, Resource*>(fileName, tempFileData));

			return tempFileData;

		}

		else if (tempFileExtension.compare(PNG) == 0) // PNG FILE
		{
			DEBUG_INFO(("Loading PNG file."));


			ImageResource* tempImageResource = NEW ImageResource(ReadImage(fileName));
			assets.insert(std::pair<std::string, Resource*>(fileName, tempImageResource));

			return tempImageResource;
		}

		else
		{
			DEBUG_WARNING(("Filetype not recognized."));
			return nullptr;
		}
	}

	else // If there is a file with the same name already.
	{
		DEBUG_INFO(("File was already in memory."));
		return GetAsset(fileName);
	}
}


/// Private Functions ///

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

std::string pm::ResourceManager::ReadFont(std::string fileName)
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
		return std::string();

}

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
		return tempBuffer;
	}
	else
		return tempBuffer; // Returns empty Image if there is an error.
}

pm::Resource* pm::ResourceManager::GetAsset(std::string fileName)
{
	assetMap::iterator it = assets.find(fileName); // Iterate through loaded Resources.

	if (it == assets.end()) // Couldn't find Resource.
	{
		DEBUG_WARNING(("Couldn't find Resource %s!", fileName.c_str()));
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
	else
		DEBUG_INFO(("ResourceManager assigned!"));

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