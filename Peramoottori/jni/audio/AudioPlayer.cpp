#include "AudioPlayer.h"

using namespace PM;

AudioPlayer::AudioPlayer()
{
	CreateEngine();
	CreateAudioPlayer();
}

void AudioPlayer::CreateEngine()
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

	if ( tempResult != SL_RESULT_SUCCESS)
		outputMixVol = nullptr;
}

bool AudioPlayer::CreateAudioPlayer()
{
	SLresult  tempResult;

	SLDataLocator_AndroidBufferQueue tempBufferQueue = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2 };
	SLDataFormat_PCM tempFormatPcm = {
		SL_DATAFORMAT_PCM, 1,
		SL_SAMPLINGRATE_8,
		SL_PCMSAMPLEFORMAT_FIXED_16,
		SL_PCMSAMPLEFORMAT_FIXED_16,
		SL_SPEAKER_FRONT_CENTER,
		SL_BYTEORDER_LITTLEENDIAN };

	SLDataSource audioSrc = { &tempBufferQueue, &tempFormatPcm };

	SLDataLocator_OutputMix tempOutmix = { SL_DATALOCATOR_OUTPUTMIX, outputMixObj };
	SLDataSink tempAudioSink = { &tempOutmix, nullptr };

	const SLInterfaceID tempIds[4] = { SL_IID_BUFFERQUEUE, SL_IID_PLAY, SL_IID_SEEK, SL_IID_VOLUME };
	const SLboolean tempReq[4] = { SL_BOOLEAN_TRUE };

	tempResult = (*engine)->CreateAudioPlayer(engine, &audioPlayerObj, &audioSrc, &tempAudioSink, 4, tempIds, tempReq);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;

	tempResult = (*audioPlayerObj)->Realize(audioPlayerObj, SL_BOOLEAN_FALSE);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;

	tempResult = (*audioPlayerObj)->GetInterface(audioPlayerObj, SL_IID_BUFFERQUEUE, &audioPlayerBufferQueue);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;

	tempResult = (*audioPlayerObj)->GetInterface(audioPlayerObj, SL_IID_PLAY, &audioPlayerPlay);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;

	tempResult = (*audioPlayerObj)->GetInterface(audioPlayerObj, SL_IID_SEEK, &audioPlayerSeek);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;

	tempResult = (*audioPlayerObj)->GetInterface(audioPlayerObj, SL_IID_VOLUME, &audioPlayerVolume);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;

	tempResult = (*audioPlayerObj)->RegisterCallback(audioPlayerObj, this->AudioPlayerCallback, nullptr);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;

	tempResult = (*audioPlayerPlay)->SetPlayState(audioPlayerPlay, SL_PLAYSTATE_PLAYING);
	PMassert::AssertEquals( tempResult, SL_RESULT_SUCCESS, nullptr);
	(void) tempResult;
}