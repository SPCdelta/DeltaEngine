#include "AudioSystem.hpp"

using namespace Audio;

void AudioSystem::Play(AudioSource& audio)
{
	audio.Play();
}

void AudioSystem::Pause(AudioSource& audio) 
{
	audio.Pause();
}

void AudioSystem::Stop(AudioSource& audio)
{
	audio.Stop();
}

void AudioSystem::Resume(AudioSource& audio)
{
	audio.Resume();
}

void AudioSystem::IncreaseVolume(AudioSource& audio, int volume)
{
	audio.IncreaseVolume(volume);
}

void AudioSystem::SetVolume(AudioSource& audio, int volume)
{
	audio.SetVolume(volume);
}
