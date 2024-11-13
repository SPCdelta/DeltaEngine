#pragma once

#include "AudioFacade.hpp"

namespace Audio
{
	class AudioSource
	{
		public:
			AudioSource(bool playOnAwake, AudioFacade& audioFacade);
			virtual void SetVolume(int volume) = 0;
			virtual void IncreaseVolume(int volume) = 0;
			virtual void Play() = 0;
			virtual void Pause() = 0;
			virtual void Resume() = 0;
			virtual void Stop() = 0;
			int GetVolume() const;
			int Loops() const; // Amount of times the chunk loops. -1 = "infinite".
			void Loop(int loops);
		protected:
			int _volume;
			int _loops;
			AudioFacade& _audioFacade;
	};
}

