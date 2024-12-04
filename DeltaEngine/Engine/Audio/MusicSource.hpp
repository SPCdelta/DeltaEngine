#pragma once

#include <SDL_mixer.h>
#include <memory>
#include <string>
#include "AudioFacade.hpp"
#include "AudioSource.hpp"

namespace Audio
{
	class MusicSource : public AudioSource
	{
		public:
			MusicSource(const std::string& path, bool playOnAwake, bool loop);
			MusicSource(const MusicSource& other);
			MusicSource& operator=(const MusicSource& other);
			MusicSource(MusicSource&& other) noexcept;
			MusicSource& operator=(MusicSource&& other) noexcept;
			~MusicSource();
			void Play() override;
			void Pause() override;
			void Resume() override;
			void Stop() override;
			void SetVolume(int volume) override;
			void IncreaseVolume(int volume) override;
			void SetClip(std::string pathToClip);
			Mix_Music* GetSource() const;
		private:
			std::unique_ptr < Mix_Music, void (*)(Mix_Music*)> _clip;
	};
}
