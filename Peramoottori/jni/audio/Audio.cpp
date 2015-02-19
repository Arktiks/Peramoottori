#include "audio/Audio.h"


pm::Audio::Audio(std::string fileName)
{
	name = fileName;

	AAsset* tempAudioAsset = pm::ResourceReader::GetInstance()->GetAsset(name);
	PMassert::AssertNotEquals(tempAudioAsset, (AAsset*)nullptr, "Reading an audio asset failed!");

	fileDescriptor = AAsset_openFileDescriptor(tempAudioAsset, &start, &length);

	if (fileDescriptor >= 0)
		PMassert::AssertEquals(true, false, "Opening audio file descriptor failed!");
	
	AAsset_close(tempAudioAsset);
}

pm::Audio::~Audio()
{
	
}

void pm::Audio::Play()
{
	AudioPlayer tempPlayer(fileDescriptor, start, length);

	tempPlayer.SetPlayState(true);

}

void pm::Audio::Stop()
{
	
}
