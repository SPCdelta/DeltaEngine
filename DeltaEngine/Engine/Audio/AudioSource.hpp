#pragma once

#include "AudioFacade.hpp"
#include "../MemLeakDetection/MemLeakDetection.hpp"
#include "../Transform.hpp"
#include <string>

namespace Audio
{
	class AudioSource : public Transform
	{
	public:
		AudioSource(bool playOnAwake, AudioFacade& audioFacade, std::string path, bool loop);
		AudioSource(const AudioSource& other);
		AudioSource& operator=(const AudioSource& other);
		AudioSource(AudioSource&& other) noexcept;
		AudioSource& operator=(AudioSource&& other) noexcept;
		~AudioSource();
		virtual void SetVolume(int volume) = 0;
		virtual void IncreaseVolume(int volume) = 0;
		virtual void Play() = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual void Stop() = 0;
		int GetVolume() const;
		bool PlayOnAwake() const;
		bool Loop() const;
		void Loop(bool loop);
	protected:
		bool _playOnAwake;
		std::string _path;
		int _volume;
		bool _loop;
		AudioFacade& _audioFacade;
	};
}