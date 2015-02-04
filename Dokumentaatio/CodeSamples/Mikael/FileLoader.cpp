#include "FileLoader.h"

using namespace PORT;

FileLoader* FileLoader::instance = nullptr;

FileLoader* FileLoader::getInstance()
{
	if (instance == nullptr)
		instance = new FileLoader;

	return instance;
}

std::string FileLoader::loadFile(std::string filePath)
{
	std::string buffer;

#if defined WIN32

	FILE * file;
	fopen_s(&file, filePath.c_str(), "r");
	if (file == NULL)
	{
		fclose(file);
		return NULL;
	}
	else
	{
		char lineHeader[128];
		std::ifstream stream(file);

		while (stream.getline(lineHeader, sizeof(lineHeader), '\n'))
		{
			buffer = buffer + lineHeader + '\n';
		}
	}

	fclose(file);

#elif defined ANDROID
	LOG("File reading start");
	AAsset* object = AAssetManager_open(manager, filePath.c_str(), 0);
	
	int fileSize = AAsset_getLength(object);
	char *temp = new char[fileSize];
	
	AAsset_read(object, temp, fileSize * sizeof(char));

	LOG("fileSize %i", fileSize);

	buffer.assign(temp, fileSize);
	
	delete temp;

	AAsset_close(object);

#endif

	return buffer;
}