#ifndef AUDIORESOURCE_H
#define AUDIORESOURCE_H

#include <resources\Resource.h>

namespace pm
{
	class AudioResource : public Resource
	{
		friend class Audio;
	public:

		AudioResource(int fileDescriptorData, off_t aLength, off_t aStart)
		: fileDescriptor(fileDescriptorData), length(aLength), start(aStart) {};

		int GetFileDescriptor() { return fileDescriptor; }

		~AudioResource() { /* AudioAsset should be closed perhaps? */ };

	private:
		int fileDescriptor;
		off_t length, start;

	};
}

#endif // AUDIORESOURCE_H