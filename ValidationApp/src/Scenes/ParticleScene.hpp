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
			ParticleEmitterConfiguration(
				"player",
				20,
				0.25f,
				false,

				2.5f, 5.0f,

				0.25f, 0.5f,

				0.0f, 360.0f,
				0.25f, 0.5f
			)
		);
		particleEmitter->Start();
	}
};