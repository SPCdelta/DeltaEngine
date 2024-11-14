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
			std::string musicPath = "../../../../ValidationApp/assets/audio/music/minecraft_theme1.mp3";
			std::string sfxPath = "creeper_explosion.mp3";
			SFXSource music{"E:/Jaar 4/Minor/SPCPRJ13/DeltaEngine/ValidationApp/assets/audio/sfx/creeper_explosion.mp3",true, audioFacade};
		}
};
