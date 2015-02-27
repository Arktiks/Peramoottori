#include "AudioPlayer.h"

pm::AudioPlayer::AudioPlayer(int fileDescriptor, off_t start, off_t length)
{
	(this)->fileDescriptor = fileDescriptor;
	(this)->start = start;
	(this)->length = length;
}

pm::AudioPlayer::AudioPlayer(AudioPlayer* pointer)
{
	fileDescriptor = pointer->fileDescriptor;
	start = pointer->start;
	length = pointer->length;
}

pm::AudioPlayer::~AudioPlayer()
{
	if (audioPlayerObj != NULL)
	{
		(*audioPlayerObj)->Destroy(audioPlayerObj);

		audioPlayerObj = NULL;
		audioPlayerPlay = NULL;
		audioPlayerSeek = NULL;
		audioPlayerVol = NULL;
	}
}

SLuint32 pm::AudioPlayer::GetPlayState()
{
	SLuint32 tempReturnValue;
	result = (*audioPlayerPlay)->GetPlayState(audioPlayerPlay, &tempReturnValue);
	CheckError("Getting OpenSL audio play state failed");

	return tempReturnValue;
}

void pm::AudioPlayer::SetPlayState(SLuint32 state)
{
	if (audioPlayerPlay != NULL)
	{
		result = (*audioPlayerPlay)->SetPlayState(audioPlayerPlay, state);
		CheckError("Setting OpenSL audio play state failed");
	}
}

void pm::AudioPlayer::SetLooping(bool isEnabled)
{
	result = (*audioPlayerSeek)->SetLoop(audioPlayerSeek, isEnabled ? SL_BOOLEAN_TRUE : SL_BOOLEAN_FALSE, 0, SL_TIME_UNKNOWN);
	CheckError("Setting OpenSL audio loop state failed");
}

void pm::AudioPlayer::SetVolume(float volPercentage)
{
	SLmillibel tempVol;
	result = (*audioPlayerVol)->GetMaxVolumeLevel(audioPlayerVol, &tempVol);

	tempVol *= 0.01 * volPercentage;

	result = (*audioPlayerVol)->SetVolumeLevel(audioPlayerVol, tempVol);
	CheckError("Setting audio volume levels failed");
}

void pm::AudioPlayer::CheckError(std::string errorText)
{
	//PMassert::AssertEquals(result, SL_RESULT_SUCCESS, errorText);
	(void)result;
}
