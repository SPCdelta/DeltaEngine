#pragma once

#include <SDL_mixer.h>

namespace Audio
{
	constexpr auto AUDIO_FREQ = 48000; // in Hz.
	constexpr auto CHANNEL_COUNT = 2; // 1 = mono, 2 = stereo, 3+ advanced surround sound.
	constexpr auto CHUNK_SIZE = 2048; // Change this value if audio drops or the latency is too low.
	constexpr auto DEFAULT_CHANNEL = -1;
	constexpr auto AUDIO_ERROR = -1;
	constexpr auto CURRENT_VOLUME = -1;
	constexpr auto DEFAULT_VOLUME = 8;

	class AudioManager
	{
	public:
		static AudioManager& GetInstance()
		{
			return _instance;
		}

		AudioManager();
		~AudioManager();

		AudioManager(const AudioManager& other) = delete;
		AudioManager& operator=(const AudioManager&& other) = delete;
		AudioManager(AudioManager&& other) = delete;
		AudioManager operator=(AudioManager&& other) = delete;

		void PlayMusic(Mix_Music* music, int loops);
		void PlaySFX(Mix_Chunk* sfx, int loops, int channel = DEFAULT_CHANNEL);

		void PauseMusic();
		void PauseSFX();

		void ResumeMusic();
		void ResumeSFX();

		void StopMusic();
		void StopSFX();

		void SetMusicVolume(int volume);
		void SetSFXVolume(Mix_Chunk* sfx, int volume);

		void IncreaseMusicVolume(int volume);
		void IncreaseSFXVolume(Mix_Chunk* sfx, int volume);

	private:
		static AudioManager _instance;
	};
}