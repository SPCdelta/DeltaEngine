#pragma once

#include <vector>

#include "../../GameObject.hpp"
#include "../../Core/Time.hpp"

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
		_started = true;
	}

	void Stop()
	{ 
		_started = false;
		// TODO
	}

	void SetLoop(bool looping) { _configuration.loop = looping; }

protected:
	GameObject* _gameObject;

	Particle* CreateParticle()
	{ 
		std::shared_ptr<GameObject> particleObj = Instantiate();
		particleObj->AddComponent<Sprite>(_configuration.sprite)->SetLayer(Layer::Particles);

		Particle* particle = _particles.emplace_back(
			new Particle
			{
				particleObj->transform,
				GetDirection(),
				GetSpeed(),
				GetRotationSpeed(),
				_configuration.particleLifeTime
			}
		);

		particle->transform->position = _gameObject->transform->position;
		particle->transform->scale = GetScale();

		return particle;
	}

	Vector2 GetDirection()
	{
		return { 1.0f, 0.0f };
	}

	float GetSpeed()
	{
		return 0.25f;
	}

	float GetRotationSpeed()
	{
		return 0.25f;
	}

	Vector2 GetScale()
	{
		return { 0.25f, 0.25f };
	}

private:
	ParticleEmitterConfiguration _configuration;
	std::vector<Particle*> _particles{};
	bool _started{ false };

	std::shared_ptr<GameObject> Instantiate()
	{
		return _gameObject->Instantiate();
	}

	void Destroy(Particle* gameObject)
	{ 
		_gameObject->Destroy(gameObject->transform->gameObject);
	}

	void Update()
	{
		if (!_started)
			return;

		_particles.erase(std::remove_if(_particles.begin(), _particles.end(),
			[this](Particle* particle)
			{
				if (particle->aliveFor <= 0.0f)
				{
					Destroy(particle);
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