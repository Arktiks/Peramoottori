#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "resources\AudioResource.h"
#include <sys/types.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <string>
#include <memory>

namespace pm
{ 
	class AudioPlayer 
	{
		friend class AudioManager;

	public:
		/**
		*Constructor for AudioPlayer.
		*/
		AudioPlayer(AudioResource* audioResourcePointer)
			: audioResource(audioResourcePointer) {};

		AudioPlayer(AudioPlayer* pointer);
		~AudioPlayer();

		/**
		* Get current playstate from AudioPlayer,
		* that can be:
		* 1 = SL_PLAYSTATE_STOPPED
		* 2 = SL_PLAYSTATE_PAUSED
		* 3 = SL_PLAYSTATE_PLAYING
		*/
		SLuint32 GetPlayState();

		void SetPlayState(SLuint32 state);

		/**
		*Sets the player to loop sfx.
		*/
		void SetLooping(bool isEnabled); 

		/**
		*Sets the players volume.
		*/
		void SetVolume(float volPercentage);

		/**
		*Returns handle to an AudioResource.
		*/
		AudioResource* getAudioResource(){return audioResource;};

	private:
		void CheckError(std::string errorText);

		SLObjectItf audioPlayerObj;
		SLPlayItf audioPlayerPlay;
		SLSeekItf audioPlayerSeek;
		SLVolumeItf audioPlayerVol;

		SLresult result;

		AudioResource* audioResource;

		int fileDescriptor;
		off_t start, length;
	};
}

#endif //AUDIOPLAYER_H