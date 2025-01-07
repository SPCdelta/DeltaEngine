#include "AudioSource.hpp"
#include <SDL_mixer.h>

using namespace Audio;

AudioSource::AudioSource(bool playOnAwake, const std::string& path, int loops)
	: _loops(loops),
	  _volume(DEFAULT_VOLUME),
	  _audioName(path),
	  _playOnAwake(playOnAwake)
{

}

AudioSource::AudioSource(const AudioSource& other)
	: _loops(other._loops),
	  _volume(other._volume),
	  _audioName(other._audioName),
	  _playOnAwake(other._playOnAwake)
{
}

AudioSource& AudioSource::operator=(const AudioSource& other)
{
	if (this != &other)
	{
		_loops = other._loops;
		_volume = other._volume;
		_audioName = other._audioName;
		_playOnAwake = other._playOnAwake;
	}
	return *this;
}

AudioSource::AudioSource(AudioSource&& other) noexcept
	: _loops(other._loops),
	  _volume(other._volume),
	  _audioName(other._audioName),
	  _playOnAwake(other._playOnAwake)
{
}

AudioSource& AudioSource::operator=(AudioSource&& other) noexcept
{
	if (this != &other)
	{
		_loops = other._loops;
		_volume = other._volume;
		_audioName = other._audioName;
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
	return _loops;
}

void AudioSource::Loop(bool loop) 
{
	_loops = loop;
}
