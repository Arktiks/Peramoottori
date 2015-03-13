#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "AudioPlayer.h"
#include "System/PMdebug.h"


namespace pm
{
	class AudioManager
	{
	public:
		static AudioManager* GetInstance();

		void InitAudioPlayer(AudioPlayer* player);
		
	private:
		void CreateEngine();
		void CheckError(std::string errorText);

		AudioManager();
		AudioManager(AudioManager* pointer);
		~AudioManager();		

		SLresult result;

		SLObjectItf engineObj;
		SLEngineItf engine;

		SLObjectItf outputMixObj;
		SLVolumeItf outputMixVol;

		static AudioManager* instance;
	};
}

#endif //AUDIOMANAGER_H