#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "System/PMassert.h"

#include <sys/types.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

namespace pm
{ 
	class AudioPlayer
	{
	public:

		AudioPlayer(int fileDescriptor, off_t start, off_t length);
		~AudioPlayer();

		void SetPlayState(bool isPlaying);
		void SetLooping(bool isEnabled);


	private:
		
		void CreateAudioPlayer();
		void CreateEngine();

		SLObjectItf engineObj;
		SLEngineItf engine;
		
		SLObjectItf outputMixObj;
		SLVolumeItf outputMixVol;

		SLObjectItf audioPlayerObj;
		SLPlayItf audioPlayerPlay;
		SLSeekItf audioPlayerSeek;
		SLVolumeItf audioPlayerVol;

		int fileDescriptor;
		off_t start, length;

	};
}

#endif //AUDIOPLAYER_H