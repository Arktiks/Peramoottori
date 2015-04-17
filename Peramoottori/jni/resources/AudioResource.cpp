#include "AudioResource.h"

pm::AudioResource::AudioResource(int fileDescriptorData, AAsset *audioAssetData)
{
	fileDescriptor = fileDescriptorData;
	AudioAsset = audioAssetData;
}
 
int pm::AudioResource::getFileDescriptor()
{
	return fileDescriptor;
}

AAsset* pm::AudioResource::getAudioAsset()
{
	return AudioAsset;
}

pm::AudioResource::~AudioResource()
{
	// AudioAsset should be closed perhaps?
}