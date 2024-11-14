#include "AudioSource.hpp"
#include <SDL_mixer.h>
#include "../MemLeakDetection/MemLeakDetection.hpp"

using namespace Audio;

AudioSource::AudioSource(bool playOnAwake, AudioFacade& audioFacade)
	: _loops(0), _volume(MIX_MAX_VOLUME), _audioFacade(audioFacade)
{

}

int AudioSource::GetVolume() const
{
	return _volume;
}

int AudioSource::Loops() const
{
	return _loops;
}

void AudioSource::Loop(int loops) 
{
	_loops = loops;
}
