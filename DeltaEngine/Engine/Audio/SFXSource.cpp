#include "AudioLoader.hpp"
#include "SFXSource.hpp"

using namespace Audio;

Audio::SFXSource::SFXSource() : AudioSource(false, "", 0), _clip(std::move(AudioLoader::LoadChunk(""))) {}

SFXSource::SFXSource(const std::string& path, bool playOnAwake, int loops = 0)
	: AudioSource(playOnAwake, path, loops),
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
	AudioManager::GetInstance().SetMusicVolume(_volume);
}

SFXSource& SFXSource::operator=(const SFXSource& other)
{
	if (this != &other)
	{
		AudioSource::operator=(other);
		_clip = std::move(AudioLoader::LoadChunk(other._path));
		AudioManager::GetInstance().SetMusicVolume(_volume);
	}
	return *this;
}

SFXSource::SFXSource(SFXSource&& other) noexcept
	: AudioSource(other), _clip(std::move(other._clip))
{
	AudioManager::GetInstance().SetMusicVolume(_volume);
}

SFXSource& SFXSource::operator=(SFXSource&& other) noexcept
{
	if (this != &other)
	{
		AudioSource::operator=(other);
		_clip = std::move(other._clip);
		AudioManager::GetInstance().SetMusicVolume(_volume);
	}
	return *this;
}

Audio::SFXSource::~SFXSource() {}

void SFXSource::Play(int channel)
{
	AudioManager::GetInstance().PlaySFX(_clip.get(), _loops, channel);
}

void SFXSource::Pause()
{
	AudioManager::GetInstance().PauseSFX();
}

void SFXSource::Resume()
{
	AudioManager::GetInstance().ResumeSFX();
}

void SFXSource::Stop()
{
	AudioManager::GetInstance().StopSFX();
}

void SFXSource::SetVolume(int volume)
{
	AudioManager::GetInstance().SetSFXVolume(_clip.get(), volume);
}

void SFXSource::IncreaseVolume(int volume)
{
	AudioManager::GetInstance().IncreaseSFXVolume(_clip.get(), volume);
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
