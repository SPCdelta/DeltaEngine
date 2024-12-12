#pragma once

#include <Engine/Delta.hpp>

class ParticleScene : public Scene
{
public:
	ParticleScene(const std::string& name)
		: Scene(name)
	{
		GameObject* particleEmitterObject = Instantiate({{20.0f, 10.0f}, 0.0f, {1.0f, 1.0f}});
		ParticleEmitter* particleEmitter = particleEmitterObject->AddComponent<ParticleEmitter>(
			// https://discussions.unity.com/t/2d-pixel-art-particles-tutorial/601613
			ParticleEmitterConfiguration(
				// Sprites
				{ "particle_big", "particle_medium_1", "particle_medium_2", "particle_small", "particle_tiny" },

				// Colors
				{ 252, 100, 0, 255 },
				{ 215, 253, 2, 255 },

				// Extra
				200,
				0.25f,

				// Particle spawn interval
				0.05f, 0.05f,
				//1.0f, 1.0f,

				// Looping
				true,

				// Lifetime
				1.5f, 2.0f,

				// Speed
				0.25f, 0.75f,

				// Rotation
				0.0f, 360.0f,
				0.0f, 0.0f
			)
		);
		particleEmitter->Start();
	}
};