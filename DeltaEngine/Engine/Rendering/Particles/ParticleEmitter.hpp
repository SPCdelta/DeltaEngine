#pragma once

#include <vector>

#include "../../GameObject.hpp"
#include "../../Core/Time.hpp"
#include "../../Core/Math/Random.hpp"
#include "../../Core/Math/Math.hpp"

#include "Particle.hpp"

struct ParticleEmitterConfiguration
{
	std::vector<std::string> sprites;
	Rendering::Color colorFrom;
	Rendering::Color colorTo;
	size_t initialSpawnAmount;

	float spawnRadius;

	float minSpawnInterval;
	float maxSpawnInterval;

	bool loop;

	// Generates a random between these two values
	float minLifetime;
	float maxLifetime;

	float minSpeed; 
	float maxSpeed;

	float minAngle;
	float maxAngle;

	float minRotationSpeed;
	float maxRotationSpeed;
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
		// TODO reset stuff
	}

	void SetLoop(bool looping) { _configuration.loop = looping; }

protected:
	GameObject* _gameObject;

	virtual Vector2 GetSpawnOffset()
	{
		return 
		{ 
			Random::NextFloat(-_configuration.spawnRadius, _configuration.spawnRadius),
			Random::NextFloat(-_configuration.spawnRadius, _configuration.spawnRadius)
		};
	}

	virtual const std::string& GetSprite()
	{
		return _configuration.sprites[static_cast<size_t>(Random::NextInt(0, static_cast<int>(_configuration.sprites.size()) - 1))];
	}

	virtual Rendering::Color GetColor()
	{
		return 
		{
			static_cast<uint8_t>(Random::NextInt(_configuration.colorFrom.r, _configuration.colorTo.r)),
			static_cast<uint8_t>(Random::NextInt(_configuration.colorFrom.g, _configuration.colorTo.g)),
			static_cast<uint8_t>(Random::NextInt(_configuration.colorFrom.b, _configuration.colorTo.b)),
			static_cast<uint8_t>(Random::NextInt(_configuration.colorFrom.a, _configuration.colorTo.a))
		};
	}

	virtual float GetLifetime()
	{
		return Random::NextFloat(_configuration.minLifetime, _configuration.maxLifetime);
	}

	virtual Vector2 GetDirection()
	{
		float angle = Random::NextFloat(_configuration.minAngle, _configuration.maxAngle);
		Vector2 direction
		{
			std::cos(angle * Math::Rad2Deg), std::sin(angle * Math::Rad2Deg)
		};

		return direction.GetNormalized();
	}

	virtual float GetSpeed()
	{ 
		return Random::NextFloat(_configuration.minSpeed, _configuration.maxSpeed);
	}

	virtual float GetRotationSpeed()
	{
		return Random::NextFloat(_configuration.minRotationSpeed, _configuration.maxRotationSpeed);
	}

	virtual Vector2 GetScale()
	{
		return { 0.25f, 0.25f };
	}

private:
	ParticleEmitterConfiguration _configuration;
	std::vector<Particle> _particles{};
	bool _started{ false };
	float _spawnParticleIn = 0.0f;

	std::shared_ptr<GameObject> Instantiate()
	{
		return _gameObject->Instantiate();
	}

	void CreateParticle()
	{ 
		std::shared_ptr<GameObject> particleObj = Instantiate();
		Sprite* sprite = particleObj->AddComponent<Sprite>(GetSprite());
		sprite->SetLayer(Layer::Particles);
		sprite->SetColor(GetColor());

		Particle& particle = _particles.emplace_back(
			particleObj.get(),
			GetDirection(),
			GetSpeed(),
			GetRotationSpeed(),
			GetLifetime()
		);

		particle.gameObject->transform->position = _gameObject->transform->position + GetSpawnOffset();
		particle.gameObject->transform->scale = GetScale();
	}

	void Destroy(size_t index)
	{
		_gameObject->Destroy(_particles[index].gameObject);
		_particles.erase(_particles.begin() + index);
	}

	void TrySpawnParticle()
	{
		if (_spawnParticleIn > 0.0f)
		{
			_spawnParticleIn -= Time::GetDeltaTime();
			return;
		}

		_spawnParticleIn = Random::NextFloat(_configuration.minSpawnInterval, _configuration.maxSpawnInterval);
		CreateParticle();
	}

	void Update()
	{
		if (!_started)
			return;

		for (size_t i = _particles.size(); i-- > 0;)
		{
			if (_particles[i].aliveFor <= 0.0f)
			{
				Destroy(i);
			}
		}

		// Spawn New Particles
		TrySpawnParticle();

		// Update Particles
		for (Particle& particle : _particles)
		{
			particle.gameObject->transform->position += (particle.direction * particle.speed * Time::GetDeltaTime());
			particle.gameObject->transform->rotation += ((360.0f / 1.0f * particle.rotationSpeed) * Time::GetDeltaTime()); // Rotations per second
			particle.aliveFor -= Time::GetDeltaTime();
		}
	}
};