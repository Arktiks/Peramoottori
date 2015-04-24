#include "AudioManager.h"
#include <core\Log.h>
#include <core\Memory.h>

pm::AudioManager* pm::AudioManager::instance = nullptr;

void AudioPlayerCallback(SLPlayItf playerObject, void* context, SLuint32 event)
{
	DEBUG_INFO(("AudioPlayer callback called."));

	if (event == SL_PLAYEVENT_HEADATEND)
	{
		DEBUG_INFO(("AudioPlayer callback event: SL_PLAYEVENT_HEADATED."));
		(*playerObject)->SetPlayState(playerObject, SL_PLAYSTATE_STOPPED);
	}
}

pm::AudioManager* pm::AudioManager::GetInstance()
{
	if (instance == nullptr)
		instance = NEW AudioManager();

	return instance;
}

void pm::AudioManager::InitAudioPlayer(AudioPlayer* player)
{
	SLDataLocator_AndroidFD locator = { SL_DATALOCATOR_ANDROIDFD, player->fileDescriptor, player->start, player->length };
	SLDataFormat_MIME format = { SL_DATAFORMAT_MIME, nullptr, SL_CONTAINERTYPE_UNSPECIFIED };
	SLDataSource audioSrc = { &locator, &format };

	SLDataLocator_OutputMix tempOutmix = { SL_DATALOCATOR_OUTPUTMIX, outputMixObj };
	SLDataSink tempAudioSink = { &tempOutmix, nullptr };

	const SLInterfaceID tempIds[3] = { SL_IID_PLAY, SL_IID_SEEK, SL_IID_VOLUME };
	const SLboolean tempReq[3] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

	result = (*engine)->CreateAudioPlayer(engine, &player->audioPlayerObj, &audioSrc, &tempAudioSink, 3, tempIds, tempReq);
	CheckError("Creating OpenSL audio player object failed!");

	result = (*player->audioPlayerObj)->Realize(player->audioPlayerObj, SL_BOOLEAN_FALSE);
	CheckError("Realizing OpenSL audio player object failed!");

	result = (*player->audioPlayerObj)->GetInterface(player->audioPlayerObj, SL_IID_PLAY, &player->audioPlayerPlay);
	CheckError("Getting OpenSL play interface failed!");

	result = (*player->audioPlayerObj)->GetInterface(player->audioPlayerObj, SL_IID_SEEK, &player->audioPlayerSeek);
	CheckError("Getting OpenSL seek interface failed!");

	result = (*player->audioPlayerObj)->GetInterface(player->audioPlayerObj, SL_IID_VOLUME, &player->audioPlayerVol);
	CheckError("Getting OpenSL volume interface failed!");

	result = (*player->audioPlayerPlay)->RegisterCallback(player->audioPlayerPlay, AudioPlayerCallback, NULL);
	CheckError("Registering OpenSL audio player callback failed!");

	result = (*player->audioPlayerPlay)->SetCallbackEventsMask(player->audioPlayerPlay, SL_PLAYEVENT_HEADATEND);
	CheckError("Setting OpenSL callback events mask failed!");

}

void pm::AudioManager::CreateEngine()
{
	result = slCreateEngine(&engineObj, 0, nullptr, 0, nullptr, nullptr);
	CheckError("Creating OpenSL engine object failed!");

	result = (*engineObj)->Realize(engineObj, SL_BOOLEAN_FALSE);
	CheckError("Realizing OpenSL engine object failed!");

	result = (*engineObj)->GetInterface(engineObj, SL_IID_ENGINE, &engine);
	CheckError("Getting OpenSL engine interface failed!");

	result = (*engine)->CreateOutputMix(engine, &outputMixObj, 0, NULL, NULL);
	CheckError("Creating OpenSL outputMix object failed!");

	result = (*outputMixObj)->Realize(outputMixObj, SL_BOOLEAN_FALSE);
	CheckError("Realizing OpenSL outpuMix object failed!");
}

void pm::AudioManager::CheckError(std::string errorText)
{
	if(result != SL_RESULT_SUCCESS)
		DEBUG_WARNING(("%s SL_RESULT #%u", errorText.c_str(), result));
	
	(void)result;
}

pm::AudioManager::AudioManager()
{
	CreateEngine();
}

pm::AudioManager::~AudioManager()
{
	if (outputMixObj != nullptr)
	{
		(*outputMixObj)->Destroy(outputMixObj);

		outputMixObj = nullptr;
		outputMixVol = nullptr;
	}

	if(engineObj != nullptr)
	{
		(*engineObj)->Destroy(engineObj);

		engineObj = nullptr;
		engine = nullptr;
	}
}