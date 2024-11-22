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
		//_sfx = {"Assets\\Audio\\SFX\\eating.mp3", false,
		auto& music = gameObject->GetComponent<Audio::MusicSource>();
		auto& sfx = gameObject->GetComponent<Audio::SFXSource>();
		music.SetClip("Assets\\Audio\\Music\\theme1.mp3");
		music.Play();
		sfx.SetClip("Assets\\Audio\\SFX\\eating.mp3");
	}
	void OnUpdate() override
	{
		auto& sfx = gameObject->GetComponent<Audio::SFXSource>();
		sfx.Play();
	}

   private:
};
