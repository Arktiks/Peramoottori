#include "AudioResource.h"

pm::AudioResource::AudioResource(int fileDescriptorData, AAsset *audioAssetData)
{
	fileDescriptor = fileDescriptorData;
	AudioAsset = audioAssetData;
}
 
int pm::AudioResource::GetFileDescriptor()
{
	return fileDescriptor;
}

AAsset* pm::AudioResource::GetAudioAsset()
{
	return AudioAsset;
}

pm::AudioResource::~AudioResource()
{
	// AudioAsset should be closed perhaps?
}