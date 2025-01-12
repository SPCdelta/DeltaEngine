#include "Registry.hpp"

bool ecs::Registry::Valid(ecs::EntityId entityId)
{
	return _registry.valid(entityId);
}

void ecs::Registry::DestroyEntity(ecs::EntityId entityId)
{
	_registry.destroy(entityId);
}
