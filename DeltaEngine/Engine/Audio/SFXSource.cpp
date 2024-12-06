#include "AudioLoader.hpp"
#include "SFXSource.hpp"

using namespace Audio;

SFXSource::SFXSource(const std::string& path, bool playOnAwake, bool loop)
	: AudioSource(playOnAwake, path, loop),
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

void SFXSource::Play()
{
	AudioManager::GetInstance().PlaySFX(_clip.get(), _loops);
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
