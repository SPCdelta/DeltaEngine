#include "MusicSource.hpp"
#include <iostream>
#include "AudioLoader.hpp"

using namespace Audio;

MusicSource::MusicSource(const std::string& path, bool playOnAwake, int loops)
	: AudioSource(playOnAwake, path, loops),
	  _clip(std::move(AudioLoader::LoadMusic(path)))
{
	PlayOnAwake();
}

MusicSource::MusicSource() : AudioSource(false, "", 0), _clip(AudioLoader::LoadMusic("")) {}

MusicSource::MusicSource(const MusicSource& other)
	: AudioSource(other), _clip(AudioLoader::LoadMusic(other._path))
{
}

MusicSource& MusicSource::operator=(const MusicSource& other)
{
	if (this != &other)
	{
		AudioSource::operator=(other);
		_clip = std::move(AudioLoader::LoadMusic(other._path));
	}
	return *this;
}

MusicSource::MusicSource(MusicSource&& other) noexcept
	: AudioSource(other), _clip(std::move(other._clip))
{
}

MusicSource& MusicSource::operator=(MusicSource&& other) noexcept
{
	if (this != &other)
	{
		AudioSource::operator=(other);
		_clip = std::move(other._clip);
	}
	return *this;
}

Audio::MusicSource::~MusicSource() {}

void MusicSource::Play()
{
	AudioManager::GetInstance().PlayMusic(_clip.get(), _loops);
}

void MusicSource::Pause()
{
	AudioManager::GetInstance().PauseMusic();
}

void MusicSource::Resume()
{
	AudioManager::GetInstance().ResumeMusic();
}

void MusicSource::Stop()
{
	AudioManager::GetInstance().StopMusic();
}

void MusicSource::SetVolume(int volume)
{
	AudioManager::GetInstance().SetMusicVolume(volume);
}

void MusicSource::IncreaseVolume(int volume)
{
	AudioManager::GetInstance().IncreaseMusicVolume(volume);
}

void MusicSource::SetClip(std::string pathToClip)
{
	_clip.reset();
	_clip = std::move(AudioLoader::LoadMusic(pathToClip));
}

Mix_Music* MusicSource::GetSource() const
{
	return _clip.get();
}
