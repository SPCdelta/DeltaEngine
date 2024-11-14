#pragma once

#include "AudioSource.hpp"

namespace Audio
{
	class AudioSystem
	{
		public:
			void Play(AudioSource& audio);
			void Pause(AudioSource& audio);
			void Stop(AudioSource& audio);
			void Resume(AudioSource& audio);
			void IncreaseVolume(AudioSource& audio, int volume);
			void SetVolume(AudioSource& audio, int volume);
	};
}
