#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <sys/types.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <string>

namespace pm
{ 
	class AudioPlayer 
	{
		friend class AudioManager;

	public:
		AudioPlayer(int fileDescriptor, off_t start, off_t length);
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

	private:
		void CheckError(std::string errorText);

		SLObjectItf audioPlayerObj;
		SLPlayItf audioPlayerPlay;
		SLSeekItf audioPlayerSeek;
		SLVolumeItf audioPlayerVol;

		SLresult result;

		int fileDescriptor;
		off_t start, length;
	};
}
#endif //AUDIOPLAYER_H