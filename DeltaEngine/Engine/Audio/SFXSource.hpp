#pragma once

#include "AudioSource.hpp"
#include <memory>
#include <string>
#include <SDL_mixer.h>
#include "AudioFacade.hpp"
#include "../MemLeakDetection/MemLeakDetection.hpp"

namespace Audio
{
	class SFXSource : public AudioSource
	{
		public:
			SFXSource(const std::string& path, bool playOnAwake,
					  AudioFacade& audioFacade);
			void Play() override;
			void Pause() override;
			void Resume() override;
			void Stop() override;
			void SetVolume(int volume) override;
			void IncreaseVolume(int volume) override;
			Mix_Chunk* GetSource() const;
		private:
			std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk*)> _source;
	};
}

