#ifndef AUDIO_H
#define AUDIO_H

#include <audio\AudioPlayer.h>
#include <string>
#include <vector>

namespace pm
{
	/** \brief Audio class contains main functionality to play audio files.
	*
	* Currently only supports <a href="https://en.wikipedia.org/wiki/Ogg">.ogg</a> files.
	* \ingroup Audio
	*/

	class Audio
	{
	public:

		/** \brief Constructor for Audio
		* \param[in] fileName Name of file you wish to create Audio object from - for example "music.ogg".
		*/
		Audio(std::string fileName);

		/** \brief Default destructor
		*/
		~Audio();

		/** \brief Starts playing audio.
		* \return false if there are no available AudioPlayers.
		*/
		bool Play();

		/** \brief Plays audio from certain location.
		* \param[in] playbackPositionAsMilliseconds Position as milliseconds.
		* \return false if there are no available AudioPlayers.
		*/
		bool PlayFrom(SLuint32 playbackPositionAsMilliseconds);

		/** \brief Stops all instances of this Audio object.
		*
		* Next time playing will start from beginning.
		*/
		void Stop();

		/** \brief Resumes all instances that are paused.
		* Playing resumes from paused location.
		* Does nothing if there are no AudioPlayers with paused playstate.
		*/
		void Resume();

		/** \brief Pauses all the instances of this Audio object.
		*
		* Next time playing will resume from paused location.
		*/
		void Pause();
		
		/** \brief Returns the playback head position of first AudioPlayer.
		*
		* Mainly used for getting the playback head position of file.
		* \return Playback head position of the first AudioPlayer in milliseconds.
		*/
		SLuint32 GetPlaybackPosition();

		/** \brief Set volume of Audio object.
		*
		* Set to maximum (100.0f) by default.
		* \param[in] volumeLevel New volume as percentage (0-100).
		*/
		void SetVolume(float volumeLevel);

		/** \brief Set Audio object looping.
		*
		* Disabled (false) by default.
		* \param[in] isEnabled True to enable looping.
		*/
		void SetLooping(bool isEnabled);

		/** \brief Defines how many instances of this Audio object can be played at once.
		*
		* Set to three instances by default.
		* \param[in] newMaxCount New maximum amount for how many instances
		* of this Audio object can be played simultaneously.
		*/
		void SetMaxPlayerCount(unsigned newMaxCount);

		/** \brief Get the file path this Audio was created from
		* \return File path of the .ogg file
		*/
		std::string GetFile(){ return file; };
		
		/** \brief Overloaded operator [] to gain access to singular AudioPlayers
		* \param[in] index of the AudioPlayer
		* \return Either AudioPlayer with index or last initialized AudioPlayer
		*/
		AudioPlayer* operator[](int index);

	private:

		Audio() = delete; // Forbid using default constructor.

		AudioPlayer* GetAvailable(); // Returns available AudioPlayer.

		std::vector<AudioPlayer*> player;
		std::string file;

		float volume;
		unsigned playerCount;
		unsigned maxPlayerCount;
	};
}

#endif // AUDIO_H