#pragma once

#include <Engine/Delta.hpp>

class ParticleScene : public Scene
{
public:
	ParticleScene(const std::string& name)
		: Scene(name)
	{
		std::shared_ptr<GameObject> particleEmitter = Instantiate({{2.0f, 2.0f}, 0.0f, {1.0f, 1.0f}});
		particleEmitter->AddComponent<ParticleEmitter>(ParticleEmitterConfiguration(
			"fire",
			20,
			5.0f)
		);
	}
};