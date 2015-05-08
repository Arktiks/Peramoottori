#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "AudioPlayer.h"

namespace pm
{
	class AudioManager
	{
	public:

		/**
		*Returns AudioManager Instance, that can be only one at once.
		*/
		static AudioManager* GetInstance();

		/**
		*Initializes AudioPlayer.
		*/
		void InitAudioPlayer(AudioPlayer* player);
		
	private:

		/**
		*Creates OPENGL soundEngine
		*/
		void CreateEngine();

		/**
		*In case of error prints them in the LogCat
		*/
		void CheckError(std::string errorText);

		AudioManager();
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