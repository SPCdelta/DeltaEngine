#include "AudioSource.hpp"
#include "AudioLoader.hpp"
#include "SFXSource.hpp"

using namespace Audio;

SFXSource::SFXSource(const std::string& path, bool playOnAwake,
					 AudioFacade& audioFacade)
	: AudioSource(playOnAwake, audioFacade), _source(std::move(AudioLoader::LoadChunk(path)))
{

}

void SFXSource::Play()
{
	_audioFacade.PlaySFX(*this);
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
	_audioFacade.SetSFXVolume(*this, volume);
}

void SFXSource::IncreaseVolume(int volume)
{
	_audioFacade.IncreaseSFXVolume(*this, volume);
}

Mix_Chunk* SFXSource::GetSource() const
{
	return _source.get();
}
