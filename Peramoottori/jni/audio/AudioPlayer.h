#include "System/PMassert.h"
#include <SLES/OpenSLES_Android.h>

namespace PM
{ 
	class AudioPlayer
	{
		AudioPlayer* GetInstance();
		bool SelectClip(Audio* audioClip, int count);

	private:
		AudioPlayer();
		~AudioPlayer();
		
		bool CreateAudioPlayer();
		void CreateEngine();
		void AudioPlayerCallback(SLAndroidSimpleBufferQueueItf bufferQueue, void *context);

		SLEngineItf engine;
		
		SLObjectItf audioPlayerObj;
		SLObjectItf engineObj;
		SLObjectItf outputMixObj;

		SLAndroidSimpleBufferQueueItf audioPlayerBufferQueue;
		SLPlayItf audioPlayerPlay;
		SLSeekItf audioPlayerSeek;
		SLVolumeItf audioPlayerVolume;
		SLVolumeItf outputMixVol;
		
		short* nextBuffer;
		unsigned nextSize;
		int nextCount;

		static AudioPlayer* instance;
	};
}