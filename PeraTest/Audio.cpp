#include "Audio.h"

Audio::Audio() : Scene("Audio")
{
	effect = new pm::Audio("Push.ogg");
	music = new pm::Audio("Midnight_Ride.ogg");

	effect->SetVolume(20.f);

	music->SetLooping(true);
	music->SetVolume(60.f);
	music->Play();
}

Audio::~Audio()
{
	delete effect;
	delete music;
}

void Audio::Update()
{
}

void Audio::Pause()
{
	effect->Play();
	pause = true;
	music->Pause();
}

void Audio::Resume()
{
	pause = false;
	music->Play();
}