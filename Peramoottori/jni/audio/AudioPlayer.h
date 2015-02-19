#include "System/PMassert.h"
#include <SLES/OpenSLES_Android.h>

namespace PM
{ 
	class AudioPlayer
	{
		AudioPlayer();
		~AudioPlayer();

	private:
		
		bool CreateAudioPlayer();
		void CreateEngine();

		SLEngineItf engine;
		
		SLObjectItf audioPlayerObj;
		SLObjectItf engineObj;
		SLObjectItf outputMixObj;

		SLAndroidSimpleBufferQueueItf audioPlayerBufferQueue;
		SLPlayItf audioPlayerPlay;
		SLSeekItf audioPlayerSeek;
		SLVolumeItf audioPlayerVolume;
		SLVolumeItf outputMixVol;
		
	};
}