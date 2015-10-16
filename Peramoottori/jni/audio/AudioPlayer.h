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
	/** \brief Ease of access class for handling OpenSL objects.
	*
	* \ingroup Audio
	*/
	class AudioPlayer
	{

		friend class AudioManager;

	public:

		///@{
		/** \brief Constructor.
		* \param[in] resource AudioResource from which you wish to create an AudioPlayer.
		* \sa pm::AudioManager::InitAudioPlayer()
		*/
		AudioPlayer(AudioResource* resource)
			: audioResource(resource) {};

		/** \brief Copy constructor.
		* \param[in] player AudioPlayer which you wish to copy from.
		* \sa pm::AudioManager::InitAudioPlayer()
		*/
		AudioPlayer(AudioPlayer* player)
			: audioResource(player->audioResource) {};
		///@}

		~AudioPlayer();

		/** \brief Get current playstate from AudioPlayer.
		* \return 1 SL_PLAYSTATE_STOPPED
		* \return 2 SL_PLAYSTATE_PAUSED
		* \return 3 SL_PLAYSTATE_PLAYING
		*/
		SLuint32 GetPlayState();
		
		/** \brief Get position of playback head.
		* \return Position as milliseconds.
		*/
		SLuint32 GetPlaybackPosition();

		/** \brief Set playstate for AudioPlayer.
		* \return 1 SL_PLAYSTATE_STOPPED
		* \return 2 SL_PLAYSTATE_PAUSED
		* \return 3 SL_PLAYSTATE_PLAYING
		*/
		void SetPlayState(SLuint32 state);

		/** \brief Set player to loop sound.
		* \param[in] isEnabled true if player should loop.
		*/
		void SetLooping(bool isEnabled); 

		/** \brief Seek a position in audio to start playing from.
		* \param[in] playbackPosition as milliseconds.
		*/
		void SetPosition(SLmillisecond playbackPosition);

		/** \brief Set player volume.
		* \param[in] volPercentage New volume as percentage (0-100).
		*/
		void SetVolume(float volPercentage);

		/**
		* \return Handle to AudioResource.
		*/
		AudioResource* GetAudioResource() { return audioResource; }

	private:

		/// Checks if SLresult != SL_RESULT_SUCCESS and displays a given error message.
		void CheckError(std::string errorText);

		/// Calculates the correct decibel value based on volPercentage given to SetVolume.
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