#pragma once

#include <SDL_mixer.h>
#include "MusicSource.hpp"
#include "SFXSource.hpp"

namespace Audio
{
	constexpr auto AUDIO_FREQ = 48000; // in Hz.
	constexpr auto CHANNEL_COUNT = 2; // 1 = mono, 2 = stereo, 3+ advanced surround sound.
	constexpr auto CHUNK_SIZE = 2048; // Change this value if audio drops or the latency is too low.
	constexpr auto DEFAULT_CHANNEL = -1;
	constexpr auto AUDIO_ERROR = -1;
	constexpr auto CURRENT_VOLUME = -1;
	class AudioFacade
	{
	public:
		AudioFacade() = default;
		AudioFacade(const AudioFacade& other) = delete;
		AudioFacade& operator=(const AudioFacade&& other) = delete;
		AudioFacade(AudioFacade&& other) = delete;
		AudioFacade operator=(AudioFacade&& other) = delete;
		~AudioFacade();
		void PlayMusic(MusicSource& music);
		void PlaySFX(SFXSource& sfx);
		void PauseMusic();
		void PauseSFX();
		void ResumeMusic();
		void ResumeSFX();
		void StopMusic();
		void StopSFX();
		void SetMusicVolume(int volume);
		void SetSFXVolume(SFXSource& sfx, int volume);
		void IncreaseMusicVolume(int volume);
		void IncreaseSFXVolume(SFXSource& sfx, int volume);
	private:
	};
}

