#include "audio\AudioPlayer.h"

SLEngineItf pm::AudioPlayer::engine = NULL;
SLObjectItf pm::AudioPlayer::engineObj = NULL;
int pm::AudioPlayer::audioPlayerCount = 0;


pm::AudioPlayer::AudioPlayer(int fileDescriptor, off_t start, off_t length)
{
	(this)->fileDescriptor = fileDescriptor;
	(this)->start = start;
	(this)->length = length;

	if (engine == NULL)
		CreateEngine();

	CreateAudioPlayer();

	audioPlayerCount++;
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

		audioPlayerCount--;
	}

	if (audioPlayerCount <= 0)
	{
		if (outputMixObj != NULL)
		{
			(*outputMixObj)->Destroy(outputMixObj);
			outputMixObj = NULL;
			outputMixVol = NULL;
		}
		
		if (engineObj != NULL)
		{
			(*engineObj)->Destroy(engineObj);
			engineObj = NULL;
			engine = NULL;
		}
	}
}

void pm::AudioPlayer::CreateEngine()
{
	SLresult  tempResult;
	
	tempResult = slCreateEngine(&engineObj, 0, nullptr, 0, nullptr, nullptr);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;

	tempResult = (*engineObj)->Realize(engineObj, SL_BOOLEAN_FALSE);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;
		
	tempResult = (*engineObj)->GetInterface(engineObj, SL_IID_ENGINE, &engine);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;

	const SLInterfaceID tempIds[] = { SL_IID_VOLUME };
	const SLboolean tempReq[] = { SL_BOOLEAN_TRUE };

	tempResult = (*engine)->CreateOutputMix(engine, &outputMixObj, 4, tempIds, tempReq);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;
	
	tempResult = (*outputMixObj)->Realize(outputMixObj, SL_BOOLEAN_FALSE);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;
	
	tempResult = (*outputMixObj)->GetInterface(outputMixObj, SL_IID_VOLUME, &outputMixVol);

	if (tempResult != SL_RESULT_SUCCESS)
		outputMixVol = nullptr;
}

void pm::AudioPlayer::CreateAudioPlayer()
{
	SLresult  tempResult;

	SLDataLocator_AndroidFD locator = { SL_DATALOCATOR_ANDROIDFD, fileDescriptor, start, length };
	SLDataFormat_MIME format = { SL_DATAFORMAT_MIME, nullptr, SL_CONTAINERTYPE_UNSPECIFIED };
	SLDataSource audioSrc = { &locator, &format };

	SLDataLocator_OutputMix tempOutmix = { SL_DATALOCATOR_OUTPUTMIX, outputMixObj };
	SLDataSink tempAudioSink = { &tempOutmix, nullptr };

	const SLInterfaceID tempIds[3] = { SL_IID_PLAY, SL_IID_SEEK, SL_IID_VOLUME };
	const SLboolean tempReq[3] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

	tempResult = (*engine)->CreateAudioPlayer(engine, &audioPlayerObj, &audioSrc, &tempAudioSink, 3, tempIds, tempReq);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;

	tempResult = (*audioPlayerObj)->Realize(audioPlayerObj, SL_BOOLEAN_FALSE);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;

	tempResult = (*audioPlayerObj)->GetInterface(audioPlayerObj, SL_IID_PLAY, &audioPlayerPlay);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;

	tempResult = (*audioPlayerObj)->GetInterface(audioPlayerObj, SL_IID_SEEK, &audioPlayerSeek);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;

	tempResult = (*audioPlayerObj)->GetInterface(audioPlayerObj, SL_IID_VOLUME, &audioPlayerVol);
	PMassert::AssertEquals(tempResult, SL_RESULT_SUCCESS, nullptr);
	(void)tempResult;
}

void pm::AudioPlayer::SetLooping(bool isEnabled)
{
	SLresult tempResult;

	tempResult = (*audioPlayerSeek)->SetLoop(audioPlayerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
	PMassert::AssertEquals(tempResult, SL_RESULT_SUCCESS, nullptr);
	(void)tempResult;
}

void pm::AudioPlayer::SetPlayState(bool isPlaying)
{
	SLresult tempResult;

	if (audioPlayerPlay != NULL)
	{
		tempResult = (*audioPlayerPlay)->SetPlayState(audioPlayerPlay, isPlaying ? SL_PLAYSTATE_PLAYING : SL_PLAYSTATE_PAUSED);
		PMassert::AssertEquals(tempResult, SL_RESULT_SUCCESS, nullptr);
		(void)tempResult;
	}
}