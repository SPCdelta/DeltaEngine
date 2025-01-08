#include "Registry.hpp"

bool ecs::Registry::Valid(ecs::EntityId entityId)
{
	return _registry.valid(entityId);
}
