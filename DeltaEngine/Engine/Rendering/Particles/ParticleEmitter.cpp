#include "ParticleEmitter.hpp"

ParticleEmitter::ParticleEmitter(GameObject* gameObject, ParticleEmitterConfiguration configuration)
	: _gameObject{ gameObject }, 
	  _configuration{ configuration }
{

}

void ParticleEmitter::Start()
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

void ParticleEmitter::Stop()
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

void ParticleEmitter::SetLoop(bool looping)
{
	_configuration.loop = looping;
}

bool ParticleEmitter::IsPlaying() const
{
	return _started;
}

std::shared_ptr<GameObject> ParticleEmitter::Instantiate()
{
	return _gameObject->Instantiate();
}

void ParticleEmitter::CreateParticle()
{ 
	std::shared_ptr<GameObject> particleObj = Instantiate();
	Sprite* sprite = particleObj->AddComponent<Sprite>(GetSprite());

	sprite->SetLayer(Layer::Particles);
	sprite->SetColor(GetColor());

	particleObj->transformRef.position = _gameObject->transformRef.position + GetSpawnOffset();
	particleObj->transformRef.scale = GetScale();

	Particle& particle = _particles.emplace_back
	(
		particleObj,
		GetDirection(),
		GetSpeed(),
		GetRotationSpeed(),
		GetLifetime()
	);
}

void ParticleEmitter::Destroy(size_t index)
{
	if (std::shared_ptr<GameObject> gameObject = _particles[index].gameObject.lock())
	{
		_gameObject->Destroy(gameObject.get());
		_particles.erase(_particles.begin() + index);
	}
	else
	{
		_particles.erase(_particles.begin() + index);
	}
}

void ParticleEmitter::TrySpawnParticle()
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

void ParticleEmitter::Update()
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
			gameObject->transformRef.rotation += ((FULL_ROTATION / 1.0f * particle.rotationSpeed) * Time::GetDeltaTime()); // Rotations per second
			particle.aliveFor -= Time::GetDeltaTime();
		}
	}

	_playingFor += Time::GetDeltaTime();
}
