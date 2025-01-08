#include "ParticleScene.hpp"

ParticleScene::ParticleScene(const std::string& name)
	: Scene(name)
{
	std::shared_ptr<GameObject> particleEmitterObject = Instantiate({{20.0f, 10.0f}, 0.0f, {1.0f, 1.0f}});
	ParticleEmitter* particleEmitter = particleEmitterObject->AddComponent<ParticleEmitter>
	(
		ParticleEmitterConfiguration
		{
			{ "particle_big", "particle_medium_1", "particle_medium_2", "particle_small", "particle_tiny" },

			{ 252, 100, 0, 255 },
			{ 215, 253, 2, 255 },

			// Extra (Playtime | Initial Spawn Amount | Spawn Radius)
			5.0f,
			2000,
			0.25f,

			// Interval
			0.05f, 0.05f,

			// Looping
			true,

			// Lifetime
			1.5f, 2.0f,

			// Speed
			2.0f, 3.0f,

			// Rotation
			0.0f, 360.0f,
			0.0f, 0.0f,

			// Scale
			0.25f, 0.25f
		}
	);

	InputManager::onKeyPressed(Key::KEY_U,
	[particleEmitter](Input& e)
	{ 
		if (particleEmitter->IsPlaying())
		{
			particleEmitter->Start();
		}
		else
		{
			particleEmitter->Stop();
		}
	});

	particleEmitter->Start();
}