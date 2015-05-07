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
		AudioPlayer(AudioResource* audioResourcePointer)
			: audioResource(audioResourcePointer) {};

		AudioPlayer(AudioPlayer* pointer);
		~AudioPlayer();

		/**
		* 1 = SL_PLAYSTATE_STOPPED
		* 2 = SL_PLAYSTATE_PAUSED
		* 3 = SL_PLAYSTATE_PLAYING
		*/
		SLuint32 GetPlayState();

		void SetPlayState(SLuint32 state);
		void SetLooping(bool isEnabled); 
		void SetVolume(float volPercentage);
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