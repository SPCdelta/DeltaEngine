#include "EntitySpawner.hpp"

EntitySpawner::EntitySpawner(GameObject* owner, const EntitySpawnerData data, std::function<void(std::shared_ptr<GameObject>&)> onSpawn)
	: _owner(owner), 
	  _data{ data }, 
	  _onSpawn{ onSpawn }
{

}

void EntitySpawner::OnStart()
{
	if (_data.spawnOnStart)
		DoSpawn();
	else
		_spawnIn = GetSpawnInterval();
}

void EntitySpawner::OnUpdate() 
{ 
	while (_spawnIn <= 0.0f)
		DoSpawn();
	_spawnIn -= Time::GetDeltaTime();
}

void EntitySpawner::DoSpawn()
{
	if (!_owner)
		throw std::runtime_error("EntitySpawner's owner GameObject is null!");

	// Also add remainder
	_spawnIn = GetSpawnInterval() + _spawnIn;

	for (int i = 0; i < GetSpawnAmount(); ++i)
	{
		std::shared_ptr<GameObject> entity = _owner->Instantiate({_owner->transform->position + GetPosition(), 0.0f, {1.0f, 1.0f}});
		_onSpawn(entity);
	}
}