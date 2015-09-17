#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "AudioPlayer.h"

namespace pm
{
	/**
	* Class for managing OpenSL AudioPlayer objects. To play audio use "Audio" class.
	*/
	class AudioManager
	{
	public:

		/**
		* Return AudioManager instance.
		*/
		static AudioManager* GetInstance();

		/**
		* Initializes AudioPlayer.
		*/
		void InitAudioPlayer(AudioPlayer* player);
		
	private:

		/**
		* Creates OpenSL sound engine.
		*/
		void CreateEngine();

		/**
		* Error message formatting for LogCat.
		*/
		void CheckError(std::string errorText);

		/**
		* Private constructor for AudioManager.
		*/
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

#endif // AUDIOMANAGER_H