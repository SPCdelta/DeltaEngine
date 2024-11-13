#include "AudioFacade.hpp"
#include <iostream>

using namespace Audio;

AudioFacade::AudioFacade() 
{
	Mix_OpenAudio(AUDIO_FREQ, AUDIO_S16SYS, CHANNEL_COUNT, CHUNK_SIZE);
}

AudioFacade::~AudioFacade() 
{
	Mix_CloseAudio();
}

void AudioFacade::PlayMusic(MusicSource& music) 
{
	if (Mix_PlayMusic(music.GetSource(), music.Loops()) == AUDIO_ERROR)
	{
		std::cerr << "Music could not be played.\n";
	}
}

void AudioFacade::PlaySFX(SFXSource& sfx)
{
	if (Mix_PlayChannel(DEFAULT_CHANNEL, sfx.GetSource(), sfx.Loops()) == AUDIO_ERROR)
	{
		std::cerr << "Chunk could not be played: No channel was avaliable.\n";
	}
}

void AudioFacade::PauseMusic()
{
	Mix_PauseMusic();
}

void AudioFacade::PauseSFX()
{
	Mix_Pause(DEFAULT_CHANNEL);
}

void AudioFacade::ResumeMusic()
{
	Mix_ResumeMusic();
}

void AudioFacade::ResumeSFX()
{
	Mix_Resume(DEFAULT_CHANNEL);
}

void AudioFacade::StopMusic()
{
	Mix_HaltMusic();
}

void AudioFacade::StopSFX()
{
	if (Mix_HaltChannel(DEFAULT_CHANNEL) == AUDIO_ERROR)
	{
		std::cerr << "An error has occured: Sound could not be stopped.\n";
	}
}

void AudioFacade::SetMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

void AudioFacade::SetSFXVolume(SFXSource& sfx, int volume)
{
	if (Mix_VolumeChunk(sfx.GetSource(), volume))
	{
		std::cerr << "Volume could not be set: Chunk was NULL.\n";
	}
}

void AudioFacade::IncreaseMusicVolume(int volume)
{
	SetMusicVolume(Mix_VolumeMusic(CURRENT_VOLUME) + volume);
}

void AudioFacade::IncreaseSFXVolume(SFXSource& sfx, int volume)
{
	SetSFXVolume(sfx, Mix_VolumeChunk(sfx.GetSource(), CURRENT_VOLUME) + volume);
}