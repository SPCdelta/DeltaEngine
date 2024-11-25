#pragma once

#include <iostream>
#include "Engine/Delta.hpp"

class TempBehaviour : public BehaviourScript
{
   public:
	// Components

	// Methods
	void OnStart() override
	{
		std::cout << "OnStart" << std::endl;
		// Comment het volgende deel in voor testen van audio. 
		// Muziek gaat namelijk out of scope en speelt niet op een aparte thread af. En ja, het is headphone user veilig.
		//Audio::MusicSource music = {"Assets\\Audio\\Music\\theme1.mp3", false,
		//							gameObject->GetAudioFacade(), false};
		//music.Play();
		//while (Mix_PlayingMusic() == 1) {}
		//std::cout << "OnStart" << std::endl;
	}

	void OnUpdate() override
	{
		std::cout << "OnUpdate" << std::endl;
		// Comment het volgende deel in voor testen van audio.
		// SFX gaat namelijk out of scope en speelt niet op een aparte thread af. En ja, het is headphone user veilig.
		//Audio::SFXSource sfx = {"Assets\\Audio\\SFX\\eating.mp3", false,
		//						gameObject->GetAudioFacade(), false};
		//sfx.Play();
		//while (Mix_Playing(0) == 1) {}
		//std::cout << "OnUpdate" << std::endl;
	}
};