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
	EntitySpawner(std::shared_ptr<GameObject> owner, const EntitySpawnerData data, std::function<void(std::shared_ptr<GameObject>&)> onSpawn)
		: _owner(owner), _data{ data }, _onSpawn{ onSpawn }
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
	std::shared_ptr<GameObject> _owner; 
	EntitySpawnerData _data;
	std::function<void(std::shared_ptr<GameObject>&)> _onSpawn;

	float _spawnIn = 0.0f;

	void DoSpawn()
	{
		if (!_owner)
            throw std::runtime_error("EntitySpawner's owner GameObject is null!");

		// Also add remainder
		_spawnIn = GetSpawnInterval() + _spawnIn;

		for (int i = 0; i < GetSpawnAmount(); ++i)
		{
			std::shared_ptr<GameObject> entity = _owner->Instantiate();
			entity->transform->position = _owner->transform->position + GetPosition();
			_onSpawn(entity);
		}
	}
};