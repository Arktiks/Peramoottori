#ifndef AUDIORESOURCE_H
#define AUDIORESOURCE_H

#include <resources\Resource.h>

namespace pm
{
	class AudioResource : public Resource
	{
	public:
		AudioResource();
		AudioResource(int fileDescriptorDAta, AAsset *audioAssetData);

		AAsset* getAudioAsset();
		int getFileDescriptor();

		~AudioResource();
	private:
		AAsset* AudioAsset;
		int fileDescriptor;
	};
}
#endif //!AUDIORESOURCE_H