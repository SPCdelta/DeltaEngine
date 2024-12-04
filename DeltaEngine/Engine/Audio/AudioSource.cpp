#include "AudioSource.hpp"
#include <SDL_mixer.h>

using namespace Audio;

AudioSource::AudioSource(bool playOnAwake, std::string path, bool loop)
	: _loop(loop),
	  _volume(MIX_MAX_VOLUME),
	  _path(path),
	  _playOnAwake(playOnAwake)
{

}

AudioSource::AudioSource(const AudioSource& other)
	: _loop(other._loop),
	  _volume(other._volume),
	  _path(other._path),
	  _playOnAwake(other._playOnAwake)
{
}

AudioSource& AudioSource::operator=(const AudioSource& other)
{
	if (this != &other)
	{
		_loop = other._loop;
		_volume = other._volume;
		_path = other._path;
		_playOnAwake = other._playOnAwake;
	}
	return *this;
}

AudioSource::AudioSource(AudioSource&& other) noexcept
	: _loop(other._loop),
	  _volume(other._volume),
	  _path(other._path),
	  _playOnAwake(other._playOnAwake)
{
}

AudioSource& AudioSource::operator=(AudioSource&& other) noexcept
{
	if (this != &other)
	{
		_loop = other._loop;
		_volume = other._volume;
		_path = other._path;
		_playOnAwake = other._playOnAwake;
	}
	return *this;
}

AudioSource::~AudioSource() {}

int AudioSource::GetVolume() const
{
	return _volume;
}

bool AudioSource::PlayOnAwake() const
{
	return _playOnAwake;
}

bool AudioSource::Loop() const
{
	return _loop;
}

void AudioSource::Loop(bool loop) 
{
	_loop = loop;
}
