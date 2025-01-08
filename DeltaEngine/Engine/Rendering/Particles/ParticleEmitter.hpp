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

	float playTime;
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

	float minScale;
	float maxScale;
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
		if (_started)
		{
			Stop();
		}

		for (size_t i = 0; i < _configuration.initialSpawnAmount; i++)
		{
			CreateParticle();
		}
		_started = true;
	}

	void Stop()
	{ 
		_started = false;
		_playingFor = 0.0f;
		_spawnParticleIn = 0.0f;

		for (size_t i = _particles.size(); i-- > 0;)
		{
			Destroy(i);
		}
		_particles.clear();
	}

	void SetLoop(bool looping) { _configuration.loop = looping; }
	bool IsPlaying() const { return _started; }

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
		return 
		{ 
			Random::NextFloat(_configuration.minScale, _configuration.maxScale),
			Random::NextFloat(_configuration.minScale, _configuration.maxScale)
		};
	}

private:
	ParticleEmitterConfiguration _configuration;
	std::vector<Particle> _particles{};
	bool _started{ false };
	float _spawnParticleIn = 0.0f;
	float _playingFor = 0.0f;

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
		particleObj->transformRef.position = _gameObject->transformRef.position + GetSpawnOffset();
		particleObj->transformRef.scale = GetScale();

		Particle& particle = _particles.emplace_back(
			particleObj,
			GetDirection(),
			GetSpeed(),
			GetRotationSpeed(),
			GetLifetime()
		);
	}

	void Destroy(size_t index)
	{
		if (std::shared_ptr<GameObject> gameObject = _particles[index].gameObject.lock())
		{
			gameObject->Destroy();
			_particles.erase(_particles.begin() + index);
		}
		else
		{
			_particles.erase(_particles.begin() + index);
		}

	}

	void TrySpawnParticle()
	{
		if (_spawnParticleIn > 0.0f)
		{
			_spawnParticleIn -= Time::GetDeltaTime();
			return;
		}

		// Take into account that all extra time that passed should be processed, not lost
		while (_spawnParticleIn <= 0.0f)
		{
			_spawnParticleIn = Random::NextFloat(_configuration.minSpawnInterval, _configuration.maxSpawnInterval) - _spawnParticleIn;
			CreateParticle();
		}
	}

	void Update()
	{
		if (!_started)
			return;

		if (!_configuration.loop && _playingFor >= _configuration.playTime)
		{
			_started = false;

			for (size_t i = _particles.size(); i-- > 0;)
			{
				Destroy(i);
			}
		}

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
			if (std::shared_ptr<GameObject> gameObject = particle.gameObject.lock())
			{
				gameObject->transformRef.position += (particle.direction * particle.speed * Time::GetDeltaTime());
				gameObject->transformRef.rotation += ((360.0f / 1.0f * particle.rotationSpeed) * Time::GetDeltaTime()); // Rotations per second
				particle.aliveFor -= Time::GetDeltaTime();
			}
		}

		_playingFor += Time::GetDeltaTime();
	}
};