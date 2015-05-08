#include "AudioPlayer.h"
#include <math.h>
#include <core/Log.h>

pm::AudioPlayer::AudioPlayer(AudioPlayer* pointer)
{
	audioResource = pointer->audioResource;
}

pm::AudioPlayer::~AudioPlayer()
{
	if (audioPlayerObj != nullptr)
	{
		(*audioPlayerObj)->Destroy(audioPlayerObj);

		audioPlayerObj = nullptr;
		audioPlayerPlay = nullptr;
		audioPlayerSeek = nullptr;
		audioPlayerVol = nullptr;
	}
}

SLuint32 pm::AudioPlayer::GetPlayState()
{
	SLuint32 tempReturnValue;
	result = (*audioPlayerPlay)->GetPlayState(audioPlayerPlay, &tempReturnValue);
	CheckError("Getting OpenSL audio play state failed!");

	return tempReturnValue;
}

void pm::AudioPlayer::SetPlayState(SLuint32 state)
{
	if(audioPlayerPlay != nullptr)
	{
		result = (*audioPlayerPlay)->SetPlayState(audioPlayerPlay, state);
		CheckError("Setting OpenSL audio play state failed!");
	}
}

void pm::AudioPlayer::SetLooping(bool isEnabled)
{
	result = (*audioPlayerSeek)->SetLoop(audioPlayerSeek, isEnabled ? SL_BOOLEAN_TRUE : SL_BOOLEAN_FALSE, 0, SL_TIME_UNKNOWN);
	CheckError("Setting OpenSL audio loop state failed!");
}

void pm::AudioPlayer::SetVolume(float volPercentage)
{
	float tempVol = volPercentage;
	tempVol *= 0.01;

	result = (*audioPlayerVol)->SetVolumeLevel(audioPlayerVol, gain_to_attenuation(tempVol)*100);
	CheckError("Setting audio volume levels failed!");
}

float pm::AudioPlayer::gain_to_attenuation(float gain)
{
	return gain < 0.01F ? -96.0F : 20 * log10(gain);
}

void pm::AudioPlayer::CheckError(std::string errorText)
{
	if (result != SL_RESULT_SUCCESS)
		DEBUG_WARNING((errorText.c_str()));
	(void)result;
}