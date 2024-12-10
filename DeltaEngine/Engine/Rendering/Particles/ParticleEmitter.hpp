#pragma once

#include <vector>

#include "Particle.hpp"

struct ParticleEmitterConfiguration
{
	std::string sprite;
	size_t initialSpawnAmount;
	float particleLifeTime;
	bool loop;
};

class ParticleSystem;

class ParticleEmitter
{
public:
	ParticleEmitter(GameObject* gameObject, ParticleEmitterConfiguration configuration)
		: _gameObject{ gameObject }, _configuration{ configuration }
	{

	}

	friend class ParticleSystem;

	void Start()
	{
		for (size_t i = 0; i < _configuration.initialSpawnAmount; i++)
		{
			CreateParticle();
		}
	}

	void SetLoop(bool looping) { _configuration.loop = looping; }

protected:
	GameObject* _gameObject;

	Particle* CreateParticle()
	{ 
		std::shared_ptr<GameObject> particle = Instantiate();
		particle->AddComponent<Sprite>(_configuration.sprite);

		return _particles.emplace_back(
			new Particle
			{
				particle->transform,
				GetDirection(),
				GetSpeed(),
				GetRotationSpeed(),
				_configuration.particleLifeTime
			}
		);
	}

	Vector2 GetDirection()
	{
		return {0.0f, 0.0f};
	}

	float GetSpeed()
	{
		return 0.25f;
	}

	float GetRotationSpeed()
	{
		return 0.25f;
	}

private:
	ParticleEmitterConfiguration _configuration;
	std::vector<Particle*> _particles{};
	bool _started{ false };

	std::shared_ptr<GameObject> Instantiate()
	{
		return _gameObject->Instantiate();
	}

	void Update()
	{
		if (!_started)
			return;

		_particles.erase(std::remove_if(_particles.begin(), _particles.end(),
			[](Particle* particle)
			{
				if (particle->aliveFor <= 0.0f)
				{
					delete particle;
					return true;
				}

				return false;
			}),_particles.end()
		);

		for (Particle* particle : _particles)
		{
			particle->transform->position += (particle->direction * particle->speed * Time::GetDeltaTime());
			particle->transform->rotation += ((360.0f / 1.0f * particle->rotationSpeed) * Time::GetDeltaTime()); // Rotations per second
			particle->aliveFor -= Time::GetDeltaTime();
		}
	}
};