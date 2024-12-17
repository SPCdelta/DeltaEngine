#pragma once

#include <Engine/Delta.hpp>

struct EntitySpawnerData
{
	float spawnIntervalMin;
	float spawnIntervalMax;

	int spawnMin;
	int spawnMax;
	bool spawnOnStart;

	float spawnRadius;
};

class EntitySpawner : public BehaviourScript
{
public:
	EntitySpawner(EntitySpawnerData data, std::function<void(std::shared_ptr<GameObject>&)> onSpawn)
		: _data{ data }, _onSpawn{ onSpawn }
	{

	}

	void OnStart()
	{
		if (_data.spawnOnStart)
		{
			DoSpawn();
		}
		else
		{
			_spawnIn = GetSpawnInterval();
		}
	}

	void OnUpdate() 
	{ 
		while (_spawnIn <= 0.0f)
		{
			DoSpawn();
		}
		_spawnIn -= Time::GetDeltaTime();
	}

protected:
	virtual int GetSpawnAmount() 
	{ 
		return Random::NextInt(_data.spawnMin, _data.spawnMax);
	}

	virtual float GetSpawnInterval()
	{
		return Random::NextFloat(_data.spawnIntervalMin, _data.spawnIntervalMax);
	}

	virtual Vector2 GetPosition()
	{
		return 
		{ 
			Random::NextFloat(-_data.spawnRadius, _data.spawnRadius),
			Random::NextFloat(-_data.spawnRadius, _data.spawnRadius)
		};
	}

private:
	EntitySpawnerData _data;
	std::function<void(std::shared_ptr<GameObject>&)> _onSpawn;

	float _spawnIn = 0.0f;

	void DoSpawn()
	{
		// Also add remainder
		_spawnIn = GetSpawnInterval() + _spawnIn;

		for (int i = 0; i < GetSpawnAmount(); ++i)
		{
			std::shared_ptr<GameObject> entity = gameObject->Instantiate();
			entity->transform->position = gameObject->transform->position + GetPosition();
			_onSpawn(entity);
		}
	}
};