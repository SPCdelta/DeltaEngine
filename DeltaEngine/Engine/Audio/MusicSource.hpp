#pragma once

#include <SDL_mixer.h>
#include <memory>
#include <string>

#include "AudioManager.hpp"
#include "AudioSource.hpp"

namespace Audio
{
	class MusicSource : public AudioSource
	{
	public:
		MusicSource();
		MusicSource(const std::string& audioName, bool playOnAwake, int loops);
		~MusicSource();

		MusicSource(const MusicSource& other);
		MusicSource& operator=(const MusicSource& other);
		MusicSource(MusicSource&& other) noexcept;
		MusicSource& operator=(MusicSource&& other) noexcept;
			
		void Play(int channel = DEFAULT_CHANNEL) override;
		void Pause() override;
		void Resume() override;
		void Stop() override;

		void SetVolume(int volume) override;
		void IncreaseVolume(int volume) override;

		void SetClip(std::string audioName);
		Mix_Music* GetSource() const;

	private:
		std::unique_ptr < Mix_Music, void (*)(Mix_Music*)> _clip;
	};
}
