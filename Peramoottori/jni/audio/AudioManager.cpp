#include "AudioManager.h"

pm::AudioManager* pm::AudioManager::instance = nullptr;

pm::AudioManager* pm::AudioManager::GetInstance()
{
	if (instance == nullptr)
		instance = new AudioManager();

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
	CheckError("Creating OpenSL audio player object failed");

	result = (*player->audioPlayerObj)->Realize(player->audioPlayerObj, SL_BOOLEAN_FALSE);
	CheckError("Realizing OpenSL audio player object failed");

	result = (*player->audioPlayerObj)->GetInterface(player->audioPlayerObj, SL_IID_PLAY, &player->audioPlayerPlay);
	CheckError("Getting OpenSL play interface failed");

	result = (*player->audioPlayerObj)->GetInterface(player->audioPlayerObj, SL_IID_SEEK, &player->audioPlayerSeek);
	CheckError("Getting OpenSL seek interface failed");

	result = (*player->audioPlayerObj)->GetInterface(player->audioPlayerObj, SL_IID_VOLUME, &player->audioPlayerVol);
	CheckError("Getting OpenSL volume interface failed");
}

void pm::AudioManager::CreateEngine()
{
	result = slCreateEngine(&engineObj, 0, nullptr, 0, nullptr, nullptr);
	CheckError("Creating OpenSL engine object failed");

	result = (*engineObj)->Realize(engineObj, SL_BOOLEAN_FALSE);
	CheckError("Realizing OpenSL engine object failed");

	result = (*engineObj)->GetInterface(engineObj, SL_IID_ENGINE, &engine);
	CheckError("Getting OpenSL engine interface failed");

	result = (*engine)->CreateOutputMix(engine, &outputMixObj, 0, NULL, NULL);
	CheckError("Creating OpenSL outputMix object failed");

	result = (*outputMixObj)->Realize(outputMixObj, SL_BOOLEAN_FALSE);
	CheckError("Realizing OpenSL outpuMix object failed");
}

void pm::AudioManager::CheckError(std::string errorText)
{
	//PMassert::AssertEquals(result, SL_RESULT_SUCCESS, errorText);
	(void)result;
}

pm::AudioManager::AudioManager()
{
	CreateEngine();
}

pm::AudioManager::AudioManager(pm::AudioManager* pointer)
{
}

pm::AudioManager::~AudioManager()
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
