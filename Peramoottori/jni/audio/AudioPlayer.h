#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <resources\AudioResource.h>
#include <sys\types.h>
#include <SLES\OpenSLES.h>
#include <SLES\OpenSLES_Android.h>
#include <string>
#include <memory>

namespace pm
{ 
	class AudioPlayer
	{

		friend class AudioManager;

	public:

		/**
		* Constructor for AudioPlayer.
		*/
		AudioPlayer(AudioResource* resource)
			: audioResource(resource) {};

		AudioPlayer(AudioPlayer* player)
			: audioResource(player->audioResource) {};

		~AudioPlayer();

		/**
		* Get current playstate from AudioPlayer:
		* 1 = SL_PLAYSTATE_STOPPED
		* 2 = SL_PLAYSTATE_PAUSED
		* 3 = SL_PLAYSTATE_PLAYING
		*/
		SLuint32 GetPlayState();

		void SetPlayState(SLuint32 state);

		/**
		* Set player to loop sound.
		*/
		void SetLooping(bool isEnabled); 

		/**
		* Set player volume.
		*/
		void SetVolume(float volPercentage);

		/**
		* Return handle to AudioResource.
		*/
		AudioResource* GetAudioResource() { return audioResource; }

	private:

		void CheckError(std::string errorText);

		float gain_to_attenuation(float gain);

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

#endif // AUDIOPLAYER_H