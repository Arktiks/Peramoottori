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
	/**
	* Ease of access class for handling OpenSL objects. Use "Audio" class instead.
	*/
	class AudioPlayer
	{

		friend class AudioManager;

	public:

		/**
		* Constructor for AudioPlayer. Create an AudioPlayer object from an AudioResource.
		* AudioPlayer must be initialized after construction. Call "pm::AudioManager::GetInstance()->InitAudioPlayer(AudioPlayer* player)"
		* to initialize an AudioPlayer.
		*/
		AudioPlayer(AudioResource* resource)
			: audioResource(resource) {};
		/**
		* Constructor for AudioPlayer. Create an AudioPlayer object from another AudioPlayer.
		* AudioPlayer must be initialized after construction. Call "pm::AudioManager::GetInstance()->InitAudioPlayer(AudioPlayer* player)"
		* to initialize an AudioPlayer.
		*/
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
		
		/**
		* Get position of playback head. Returns value as milliseconds.
		*/
		SLuint32 GetPlaybackPosition();

		/**
		* Set playstate for AudioPlayer:
		* 1 = SL_PLAYSTATE_STOPPED
		* 2 = SL_PLAYSTATE_PAUSED
		* 3 = SL_PLAYSTATE_PLAYING
		*/
		void SetPlayState(SLuint32 state);

		/**
		* Set player to loop sound.
		*/
		void SetLooping(bool isEnabled); 

		/**
		* Seek a position in audio to start playing from. Give playbackPosition as milliseconds.
		*/
		void SetPosition(SLmillisecond playbackPosition);

		/**
		* Set player volume.
		*/
		void SetVolume(float volPercentage);

		/**
		* Return handle to AudioResource.
		*/
		AudioResource* GetAudioResource() { return audioResource; }

	private:

		/**
		* Checks if SLresult != SL_RESULT_SUCCESS and displays a given error message.
		*/
		void CheckError(std::string errorText);

		/**
		* Calculates the correct decibel value based on volPercentage given to SetVolume.
		*/
		float GainToAttenuation(float gain);

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