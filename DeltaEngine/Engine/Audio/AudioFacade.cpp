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

void AudioFacade::PlayMusic(Mix_Music* music, int loops)
{
	if (Mix_PlayMusic(music, loops) == AUDIO_ERROR)
	{
		std::cerr << "Music could not be played.\n";
	}
}

void AudioFacade::PlaySFX(Mix_Chunk* sfx, int loops)
{
	if (Mix_PlayChannel(DEFAULT_CHANNEL, sfx, loops) ==
		AUDIO_ERROR)
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

void AudioFacade::SetSFXVolume(Mix_Chunk* sfx, int volume)
{
	if (Mix_VolumeChunk(sfx, volume))
	{
		std::cerr << "Volume could not be set: Chunk was NULL.\n";
	}
}

void AudioFacade::IncreaseMusicVolume(int volume)
{
	SetMusicVolume(Mix_VolumeMusic(CURRENT_VOLUME) + volume);
}

void AudioFacade::IncreaseSFXVolume(Mix_Chunk* sfx, int volume)
{
	SetSFXVolume(sfx,
				 Mix_VolumeChunk(sfx, CURRENT_VOLUME) + volume);
}
