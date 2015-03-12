#include "Audio.h"

pm::Audio::Audio(std::string fileName)
{
	maxPlayerCount = 3;
	playerCount = 1;

	AAsset* tempAudioAsset = pm::ResourceManager::GetInstance()->GetAsset(fileName);
	AAsset* tempNull = nullptr;
	//PMassert::AssertNotEquals(tempAudioAsset, tempNull, "Reading an audio asset failed!");

	off_t start, length;

	int fileDescriptor = AAsset_openFileDescriptor(tempAudioAsset, &start, &length);

	if (fileDescriptor <= 0)
	//	PMassert::AssertEquals(true, false, "Opening audio file descriptor failed!");
	
	AAsset_close(tempAudioAsset);
	
	player.push_back(new AudioPlayer(fileDescriptor, start, length));
	AudioManager::GetInstance()->InitAudioPlayer(player[0]);
}

pm::Audio::~Audio()
{
	for (int i = 0; i < playerCount; i++)
		delete &player[i];
}

bool pm::Audio::Play()
{
	AudioPlayer* tempPointer = GetAvailable();
	
	if (tempPointer != nullptr)
	{
		tempPointer->SetPlayState(SL_PLAYSTATE_PLAYING);
		return true;
	}
	else
		return false;
}

void pm::Audio::Stop()
{
	for (int i = 0; i < playerCount; i++)
		player[i]->SetPlayState(SL_PLAYSTATE_STOPPED);
}

void pm::Audio::Pause()
{
	for (int i = 0; i < playerCount; i++)
		player[i]->SetPlayState(SL_PLAYSTATE_PAUSED);
}

void pm::Audio::SetVolume(float volumeLevel)
{
	for (int i = 0; i < playerCount; i++)
		player[i]->SetVolume(volumeLevel);
}

void pm::Audio::SetLooping(bool isEnabled)
{
	for (int i = 0; i < playerCount; i++)
		player[i]->SetLooping(isEnabled);
}

void pm::Audio::SetMaxPlayerCount(unsigned newMaxCount)
{
	if (newMaxCount < maxPlayerCount)
	{
		PMdebug::MsgWarning("Removing AudioPlayers. Possible loss of data!");

		for (int i = maxPlayerCount; i > newMaxCount; i--)
		{
			delete &(player.at(i));
			player.erase(player.begin() + i);
		}		

		playerCount = newMaxCount;
		player.resize(maxPlayerCount);
	}
	maxPlayerCount = newMaxCount;
	
}

pm::AudioPlayer* pm::Audio::GetAvailable()
{
	for (int i = 0; i < player.size(); i++)
	{
		SLuint32 temp = player.at(i)->GetPlayState();
		if ( temp == SL_PLAYSTATE_STOPPED )
			return player[i];
	}
	if (playerCount < maxPlayerCount)
	{
		playerCount++;
		player[playerCount] = new AudioPlayer(player[0]);
		AudioManager::GetInstance()->InitAudioPlayer(player[playerCount]);

		return player[playerCount];
	}
	else
		return nullptr;
}