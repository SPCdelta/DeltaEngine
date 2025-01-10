#pragma once

#include "Engine/Delta.hpp"
#include "Engine/BehaviourScript.hpp"
#include <Engine/Audio/MusicSource.hpp>
#include <Engine/Audio/SFXSource.hpp>
#include <Engine/Audio/AudioLoader.hpp>

class TempAudio : public BehaviourScript
{
   public:
	void OnStart() override
	{
		auto& music = transform->gameObject->GetComponent<Audio::MusicSource>();
		//auto& sfx = gameObject->GetComponent<Audio::SFXSource>();
		music.SetClip("menu");
		music.Play();
	}

	void OnUpdate() override
	{
		//auto& sfx = gameObject->GetComponent<Audio::SFXSource>();
		//sfx.Play();
	}

   private:
};
