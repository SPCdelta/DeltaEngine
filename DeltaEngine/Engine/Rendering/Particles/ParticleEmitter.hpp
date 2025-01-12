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

constexpr float FULL_ROTATION = 360.0f;

class ParticleEmitter
{
public:
	ParticleEmitter(GameObject* gameObject, ParticleEmitterConfiguration configuration);

	friend class ParticleSystem;

	void Start();
	void Stop();

	void SetLoop(bool looping);
	bool IsPlaying() const;

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

	bool _started{false};
	float _spawnParticleIn = 0.0f;
	float _playingFor = 0.0f;

	std::shared_ptr<GameObject> Instantiate();

	void CreateParticle();
	void Destroy(size_t index);

	void TrySpawnParticle();

	void Update();
};