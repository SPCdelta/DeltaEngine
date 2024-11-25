#include "MusicSource.hpp"
#include <iostream>
#include "AudioLoader.hpp"

using namespace Audio;

MusicSource::MusicSource(const std::string& path, bool playOnAwake,
						 AudioFacade& audioFacade, bool loop)
	: AudioSource(playOnAwake, audioFacade, path, loop),
	  _clip(std::move(AudioLoader::LoadMusic(path)))
{
	PlayOnAwake();
}

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
	_audioFacade.PlayMusic(_clip.get(), _loop);
}

void MusicSource::Pause()
{
	_audioFacade.PauseMusic();
}

void MusicSource::Resume()
{
	_audioFacade.ResumeMusic();
}

void MusicSource::Stop()
{
	_audioFacade.StopMusic();
}

void MusicSource::SetVolume(int volume)
{
	_audioFacade.SetMusicVolume(volume);
}

void MusicSource::IncreaseVolume(int volume)
{
	_audioFacade.IncreaseMusicVolume(volume);
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
