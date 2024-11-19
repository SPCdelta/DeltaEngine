#pragma once
#include "../BehaviourScript.hpp"
#include "../Audio/MusicSource.hpp"
#include "../Audio/SFXSource.hpp"

using namespace Audio;

class TempAudio : public BehaviourScript
{
   public:
	void OnStart() override
	{
		//music = {"Assets\\Audio\\Music\\theme1.mp3", false,
		//		 gameObject->GetAudioFacade(), false};
		//sfx = {"Assets\\Audio\\SFX\\eating.mp3", false,
		//	   gameObject->GetAudioFacade(), false};
		//music.Play();
	}
	void OnUpdate() override {  }
	//MusicSource music;
	//SFXSource sfx;
};
