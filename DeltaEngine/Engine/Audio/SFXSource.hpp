#pragma once

#include <SDL_mixer.h>
#include <memory>
#include <string>
#include "AudioFacade.hpp"
#include "AudioSource.hpp"

namespace Audio
{
class SFXSource : public AudioSource
{
   public:
	SFXSource(const std::string& path, bool playOnAwake, bool loop);
	SFXSource(const SFXSource& other);
	SFXSource& operator=(const SFXSource& other);
	SFXSource(SFXSource&& other) noexcept;
	SFXSource& operator=(SFXSource&& other) noexcept;
	~SFXSource();
	void Play() override;
	void Pause() override;
	void Resume() override;
	void Stop() override;
	void SetVolume(int volume) override;
	void IncreaseVolume(int volume) override;
	void SetClip(std::string pathToClip);
	Mix_Chunk* GetSource() const;

   private:
	std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk*)> _clip;
};
}  // namespace Audio
