#ifndef AUDIO_H
#define AUDIO_H

#include <audio\AudioPlayer.h>
#include <string>
#include <vector>

namespace pm
{
	/**
	* Class for playing audio.
	*/
	class Audio
	{
	public:
		/**
		* Constructor for Audio class.
		*/
		Audio(std::string fileName);
		~Audio();

		/**
		* Starts playing audio.
		* Returns false if there are no available AudioPlayers.
		*/
		bool Play();

		/**
		* Stops all the instances of this Audio object.
		* Next time playing will start from the beginning.
		*/
		void Stop();

		/**
		* Pauses all the instances of this Audio object.
		* Next time playing will continue from the same point.
		*/
		void Pause();
		
		/**
		* Sets the volume to given value.
		* Give volumeLevel as percentage.
		*/
		void SetVolume(float volumeLevel);

		/**
		* Sets looping to given value.
		* 'isEnabled = true' enables looping.
		* 'isEnabled = false' disables looping.
		*/
		void SetLooping(bool isEnabled);

		/**
		* MaxPlayerCount default = 3
		* MaxPlayerCount defines how many instances of this Audio object
		* can be played at once. 
		*/
		void SetMaxPlayerCount(unsigned newMaxCount);
		
	private:

		Audio() = delete; // Forbid using default constructor.

		/**
		* Returns available AudioPlayer.
		*/
		AudioPlayer* GetAvailable();
		std::vector<AudioPlayer*> player;

		float volume;
		unsigned playerCount;
		unsigned maxPlayerCount;
	};
}

#endif // AUDIO_H