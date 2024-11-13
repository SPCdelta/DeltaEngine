#include "MusicSource.hpp"
#include "AudioLoader.hpp"
#include <iostream>

using namespace Audio;

MusicSource::MusicSource(const std::string& path, bool playOnAwake,
						 AudioFacade& audioFacade)
	: AudioSource(playOnAwake, audioFacade), _source(std::move(AudioLoader::LoadMusic(path)))
{

}

void MusicSource::Play()
{
	_audioFacade.PlayMusic(_source.get(), _loops);
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

Mix_Music* MusicSource::GetSource() const
{
	return _source.get();
}
