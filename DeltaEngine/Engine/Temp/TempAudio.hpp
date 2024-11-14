#pragma once
#include "../Audio/AudioFacade.hpp"
#include "../Audio/MusicSource.hpp"
#include "../Audio/SFXSource.hpp"
#include <filesystem>

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
			std::string musicPath = "assets/audio/music/minecraft_theme1.mp3";
			SFXSource music{musicPath,true, audioFacade};
			auto o = music.GetSource();
		}
};
