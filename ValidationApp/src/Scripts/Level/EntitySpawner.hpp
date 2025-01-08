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
	EntitySpawner(GameObject* owner, const EntitySpawnerData data, std::function<void(std::shared_ptr<GameObject>&)> onSpawn);

	void OnStart();
	void OnUpdate();

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
	GameObject* _owner; 
	EntitySpawnerData _data;
	std::function<void(std::shared_ptr<GameObject>&)> _onSpawn;

	float _spawnIn = 0.0f;

	void DoSpawn();
};