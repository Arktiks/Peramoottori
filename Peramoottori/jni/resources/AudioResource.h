#ifndef AUDIORESOURCE_H
#define AUDIORESOURCE_H

#include <resources\Resource.h>

namespace pm
{
	class AudioResource : public Resource
	{
		friend class Audio;
	public:
		/// Audioresource constructor.
		AudioResource(int fileDescriptorData, off_t aLength, off_t aStart)
		: fileDescriptor(fileDescriptorData), length(aLength), start(aStart) {};
		/// returns fileDescriptor int that AudioManager uses to define files
		int GetFileDescriptor() { return fileDescriptor; };

		/// returns the lenght of the AudioResourse
		off_t GetLength() { return length; };

		/// returns the lenght that is the distance to start 
		off_t GetStart(){ return start; };

		~AudioResource() { /* AudioAsset should be closed perhaps? NOPE*/ };

	private:
		int fileDescriptor;
		off_t length, start;

	};
}

#endif // AUDIORESOURCE_H