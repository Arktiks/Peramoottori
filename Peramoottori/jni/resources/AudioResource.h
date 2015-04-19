#ifndef AUDIORESOURCE_H
#define AUDIORESOURCE_H

#include <resources\Resource.h>

namespace pm
{
	class AudioResource : public Resource
	{
	public:

		// Doesn't work because no functions to add them after initialization.
		// AudioResource() : AudioAsset(nullptr), fileDescriptor(0) {};

		AudioResource(int fileDescriptorData, AAsset* audioAssetData) :
			fileDescriptor(fileDescriptorData), AudioAsset(audioAssetData) {};

		AAsset* GetAudioAsset() { return AudioAsset; }

		int GetFileDescriptor() { return fileDescriptor; }

		~AudioResource() { /* AudioAsset should be closed perhaps? */ };

	private:

		AAsset* AudioAsset;

		int fileDescriptor;

	};
}

#endif // AUDIORESOURCE_H