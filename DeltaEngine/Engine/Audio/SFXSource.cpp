#include "AudioLoader.hpp"
#include "SFXSource.hpp"
#include "../MemLeakDetection/MemLeakDetection.hpp"

using namespace Audio;

SFXSource::SFXSource(const std::string& path, bool playOnAwake,
					 AudioFacade& audioFacade, bool loop)
	: AudioSource(playOnAwake, audioFacade, path, loop),
	  _clip(std::move(AudioLoader::LoadChunk(path)))
{
	if (playOnAwake)
	{
		Play();
	}
}

SFXSource::SFXSource(const SFXSource& other)
	: AudioSource(other), _clip(AudioLoader::LoadChunk(other._path))
{
	_audioFacade.SetMusicVolume(_volume);
}

SFXSource& SFXSource::operator=(const SFXSource& other)
{
	if (this != &other)
	{
		AudioSource::operator=(other);
		_clip = std::move(AudioLoader::LoadChunk(other._path));
		_audioFacade.SetMusicVolume(_volume);
	}
	return *this;
}

SFXSource::SFXSource(SFXSource&& other) noexcept
	: AudioSource(other), _clip(std::move(other._clip))
{
	_audioFacade.SetMusicVolume(_volume);
}

SFXSource& SFXSource::operator=(SFXSource&& other) noexcept
{
	if (this != &other)
	{
		AudioSource::operator=(other);
		_clip = std::move(other._clip);
		_audioFacade.SetMusicVolume(_volume);
	}
	return *this;
}

Audio::SFXSource::~SFXSource() {}

void SFXSource::Play()
{
	_audioFacade.PlaySFX(_clip.get(), _loop);
}

void SFXSource::Pause()
{
	_audioFacade.PauseSFX();
}

void SFXSource::Resume()
{
	_audioFacade.ResumeSFX();
}

void SFXSource::Stop()
{
	_audioFacade.StopSFX();
}

void SFXSource::SetVolume(int volume)
{
	_audioFacade.SetSFXVolume(_clip.get(), volume);
}

void SFXSource::IncreaseVolume(int volume)
{
	_audioFacade.IncreaseSFXVolume(_clip.get(), volume);
}

void SFXSource::SetClip(std::string pathToClip)
{
	_clip.reset();
	_clip = std::move(AudioLoader::LoadChunk(pathToClip));
}

Mix_Chunk* SFXSource::GetSource() const
{
	return _clip.get();
}
