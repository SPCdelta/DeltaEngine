#pragma once

#include <Engine/Delta.hpp>

class ParticleScene : public Scene
{
public:
	ParticleScene(const std::string& name)
		: Scene(name)
	{
		std::shared_ptr<GameObject> particleEmitterObject = Instantiate({{20.0f, 10.0f}, 0.0f, {1.0f, 1.0f}});
		ParticleEmitter* particleEmitter = particleEmitterObject->AddComponent<ParticleEmitter>(
			// https://discussions.unity.com/t/2d-pixel-art-particles-tutorial/601613
			ParticleEmitterConfiguration(
				{ "particle_big", "particle_medium_1", "particle_medium_2", "particle_small", "particle_tiny" },

				{ 252, 100, 0, 255 },
				{ 215, 253, 2, 255 },

				20,
				0.25f,

				0.1f, 0.15f,

				true,

				1.5f, 2.0f,

				// Speed
				0.25f, 1.0f,

				0.0f, 360.0f,
				0.0f, 0.0f
			)
		);
		particleEmitter->Start();
	}
};