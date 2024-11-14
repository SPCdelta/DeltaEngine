#pragma once
#include "../Audio/AudioFacade.hpp"
#include "../Audio/MusicSource.hpp"
#include "../Audio/SFXSource.hpp"
#include <filesystem>
#include "../Audio/AudioSystem.hpp"

using namespace Audio;

class TempAudio
{
    public:
		TempAudio() 
		{ 
			StartAudio();
		}

		void StartAudio()
		{ 
			AudioFacade audioFacade{};
			AudioSystem audioSystem{};
			std::string musicPath = "assets/audio/music/minecraft_theme1.mp3";
			MusicSource music{musicPath, false, audioFacade};
			auto o = music.GetSource();
			audioSystem.Play(music);
		}
};
