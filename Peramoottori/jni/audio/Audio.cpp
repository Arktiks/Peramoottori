#include "Audio.h"
#include <resources\ResourceReader.h>
#include <system\PMassert.h>
#include <system\PMdebug.h>

pm::Audio::Audio(std::string fileName)
{
	AAsset* tempAudioAsset = pm::ResourceReader::GetInstance()->GetAsset(fileName);
	PMassert::AssertNotEquals(tempAudioAsset, (AAsset*)nullptr, "Reading an audio asset failed!");

	off_t start, length;

	int fileDescriptor = AAsset_openFileDescriptor(tempAudioAsset, &start, &length);

	if (fileDescriptor >= 0)
		PMassert::AssertEquals(true, false, "Opening audio file descriptor failed!");
	
	AAsset_close(tempAudioAsset);
	
	player = new AudioPlayer(fileDescriptor, start, length);
}

pm::Audio::~Audio()
{
	delete player;
}

void pm::Audio::Play()
{
	player->SetPlayState(true);
}

void pm::Audio::Stop()
{
	player->SetPlayState(false);
}

void pm::Audio::SetLooping(bool isEnabled)
{
	player->SetLooping(isEnabled);
}