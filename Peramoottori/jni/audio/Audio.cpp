#include "audio/Audio.h"

using namespace PM;

Audio::Audio(std::string fileName)
{
	
}

Audio::~Audio()
{
	
}

int Audio::GetSize()
{
	return size;
}

char* Audio::GetData()
{
	return data.data();
}