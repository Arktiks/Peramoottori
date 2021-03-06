#include "Audio.h"
#include <core\Log.h>
#include <core\Passert.h>
#include <core\Memory.h>
#include <audio\AudioManager.h>
#include <resources\ResourceManager.h>

pm::Audio::Audio(std::string fileName) : volume(100.0f), playerCount(1), maxPlayerCount(3)
{
	AudioResource* tempAudioAsset = (pm::AudioResource*)pm::ResourceManager::GetInstance()->LoadAsset(fileName);
	ASSERT_NEQUAL(tempAudioAsset, nullptr);
	player.push_back(NEW AudioPlayer(tempAudioAsset));
	AudioManager::GetInstance()->InitAudioPlayer(player[0]);
	(this->file) = fileName;
}

pm::Audio::~Audio()
{
	for (int i = 0; i < playerCount; i++)
		delete player[i];
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

bool pm::Audio::PlayFrom(SLuint32 playbackPositionAsMilliseconds)
{
	AudioPlayer* tempPointer = GetAvailable();

	if (tempPointer != nullptr)
	{
		tempPointer->SetPosition(playbackPositionAsMilliseconds);
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

void pm::Audio::Resume()
{
	for (int i = 0; i < playerCount; i++)
	{
		SLuint32 temp = player.at(i)->GetPlayState();
		if (temp == SL_PLAYSTATE_PAUSED)
			player[i]->SetPlayState(SL_PLAYSTATE_PLAYING);
	}
}

void pm::Audio::Pause()
{
	for (int i = 0; i < playerCount; i++)
		player[i]->SetPlayState(SL_PLAYSTATE_PAUSED);
}

SLuint32 pm::Audio::GetPlaybackPosition()
{
	return player[0]->GetPlaybackPosition();
}

void pm::Audio::SetVolume(float volumeLevel)
{
	volume = volumeLevel;
	for (int i = 0; i < playerCount; i++)
		player[i]->SetVolume(volume);
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
		for (int i = 0; i < playerCount; i++)
		{
			player[i]->SetPlayState(SL_PLAYSTATE_STOPPED);
		}

		DEBUG_WARNING(("Removing AudioPlayers for (%s), possible loss of data!", file.c_str()));

		for (int i = newMaxCount - 1; i < playerCount; i++)
		{
			delete player[i];
			player.erase(player.begin() + i);
			playerCount--;
		}
	}

	maxPlayerCount = newMaxCount;
}

pm::AudioPlayer* pm::Audio::GetAvailable()
{
	for (int i = 0; i < playerCount; i++)
	{
		SLuint32 temp = player.at(i)->GetPlayState();
		if (temp == SL_PLAYSTATE_STOPPED)
			return player[i];
	}

	if (playerCount < maxPlayerCount)
	{
		playerCount++;
		player.push_back(NEW AudioPlayer(player[0]));
		AudioManager::GetInstance()->InitAudioPlayer(player[playerCount - 1]);
		player[playerCount - 1]->SetVolume(volume);
		return player[playerCount-1];
	}
	else
		return nullptr;
}

pm::AudioPlayer* pm::Audio::operator[](int index)
{
	if (index < playerCount)
		return player[index];

	return player[playerCount - 1];
}