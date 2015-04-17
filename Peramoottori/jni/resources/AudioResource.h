#ifndef AUDIORESOURCE_H
#define AUDIORESOURCE_H

#include <resources\Resource.h>

namespace pm
{
	class AudioResource : public Resource
	{
	public:

		// Doesn't work because no functions to add them after initialization.
		AudioResource() : AudioAsset(nullptr), fileDescriptor(0) {};

		AudioResource(int fileDescriptorDAta, AAsset *audioAssetData);

		AAsset* GetAudioAsset();
		int GetFileDescriptor();

		~AudioResource();

	private:
		AAsset* AudioAsset;
		int fileDescriptor;

	};
}
#endif // AUDIORESOURCE_H