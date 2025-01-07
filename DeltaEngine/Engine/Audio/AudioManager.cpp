#include "AudioManager.hpp"
#include <iostream>

using namespace Audio;

AudioManager AudioManager::_instance;

AudioManager& Audio::AudioManager::GetInstance()
{
	return _instance;
}

AudioManager::AudioManager()
{
	if (Mix_OpenAudio(AUDIO_FREQ, AUDIO_S16SYS, CHANNEL_COUNT, CHUNK_SIZE) == AUDIO_ERROR)
	{
		std::cerr << "An error has occured: Audio device could not be opened.\n";
	}
}

AudioManager::~AudioManager()
{
	Mix_CloseAudio();
}

void AudioManager::PlayMusic(Mix_Music* music, int loops)
{
	if (Mix_PlayMusic(music, loops) == AUDIO_ERROR)
	{
		std::cerr << "Music could not be played.\n";
	}
}

void AudioManager::PlaySFX(Mix_Chunk* sfx, int loops, int channel)
{
	if (channel == 0)
	{
		if (Mix_PlayChannel(DEFAULT_CHANNEL, sfx, loops) == AUDIO_ERROR)
		{
			std::cerr << "Chunk could not be played: No channel was avaliable.\n";
		}
	}
	else
	{
		if (Mix_PlayChannel(channel, sfx, loops) == AUDIO_ERROR)
		{
			std::cerr << "Chunk could not be played: No channel was avaliable.\n";
		}

	}	
}

void AudioManager::PauseMusic()
{
	Mix_PauseMusic();
}

void AudioManager::PauseSFX()
{
	Mix_Pause(DEFAULT_CHANNEL);
}

void AudioManager::ResumeMusic()
{
	Mix_ResumeMusic();
}

void AudioManager::ResumeSFX()
{
	Mix_Resume(DEFAULT_CHANNEL);
}

void AudioManager::StopMusic()
{
	Mix_HaltMusic();
}

void AudioManager::StopSFX()
{
	if (Mix_HaltChannel(DEFAULT_CHANNEL) == AUDIO_ERROR)
	{
		std::cerr << "An error has occured: Sound could not be stopped.\n";
	}
}

void AudioManager::SetMusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

void AudioManager::SetSFXVolume(Mix_Chunk* sfx, int volume)
{
	if (Mix_VolumeChunk(sfx, volume) == AUDIO_ERROR)
	{
		std::cerr << "Volume could not be set: Chunk was NULL.\n";
	}
}

void AudioManager::IncreaseMusicVolume(int volume)
{
	SetMusicVolume(Mix_VolumeMusic(CURRENT_VOLUME) + volume);
}

void AudioManager::IncreaseSFXVolume(Mix_Chunk* sfx, int volume)
{
	SetSFXVolume(sfx, Mix_VolumeChunk(sfx, CURRENT_VOLUME) + volume);
}
