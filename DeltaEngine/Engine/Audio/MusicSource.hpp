#pragma once

#include <SDL_mixer.h>
#include <memory>
#include <string>
#include "AudioSource.hpp"

namespace Audio
{
	class MusicSource : public AudioSource
	{
		public:
			MusicSource(const std::string& path, bool playOnAwake,
						AudioFacade& audioFacade);
			void Play() override;
			void Pause() override;
			void Resume() override;
			void Stop() override;
			void SetVolume(int volume) override;
			void IncreaseVolume(int volume) override;
			Mix_Music* GetSource() const;
		private:
			std::unique_ptr < Mix_Music, void (*)(Mix_Music*)> _source;
	};
}
