#include "LifetimeSystem.hpp"

LifetimeSystem::LifetimeSystem(ecs::Registry& reg) 
	: ecs::System<Lifetime>(reg) 
{

}

void LifetimeSystem::Update()
{
	RefreshView();
	for (ecs::EntityId entityId : _view)
	{
		auto& life = _view.get<Lifetime>(entityId);
		life.remaining -= Time::GetDeltaTime();
		if (life.remaining <= 0)
			_reg._registry.destroy(entityId);
	}
}