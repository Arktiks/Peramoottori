#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "AudioPlayer.h"

namespace pm
{
	/** \brief Class for managing OpenSL AudioPlayer objects.
	*
	* Class has been constructed using singleton design pattern.
	* \ingroup Audio
	*/

	class AudioManager
	{
	public:

		/** \brief Return instace of AudioManager.
		*/
		static AudioManager* GetInstance();

		/** \brief Initialize given AudioPlayer.
		* \param[out] player Pointer to AudioPlayer that should be initialized.
		*/
		void InitAudioPlayer(AudioPlayer* player);
		
	private:

		void CreateEngine(); // Creates OpenSL sound engine.

		void CheckError(std::string errorText); // Error message formatting for LogCat.

		AudioManager(); // Private constructor for AudioManager.

		~AudioManager();		

		SLresult result;

		SLObjectItf engineObj;
		SLEngineItf engine;

		SLObjectItf outputMixObj;
		SLVolumeItf outputMixVol;

		static AudioManager* instance;
	};
}

#endif // AUDIOMANAGER_H