#pragma once

#include <Engine/Delta.hpp>

class ParticleScene : public Scene
{
public:
	ParticleScene(const std::string& name)
		: Scene(name)
	{
		std::shared_ptr<GameObject> particleEmitterObject = Instantiate({{2.0f, 2.0f}, 0.0f, {1.0f, 1.0f}});
		ParticleEmitter* particleEmitter = particleEmitterObject->AddComponent<ParticleEmitter>(
			ParticleEmitterConfiguration(
				"player",
				20,
				1.0f,
				false
			)
		);
		particleEmitter->Start();
	}
};