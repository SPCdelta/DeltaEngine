#include "UpdateSystem.hpp"

BehaviourSystem::BehaviourSystem(ecs::Registry& reg) 
	: ecs::System<std::unique_ptr<BehaviourScript>>(reg)
{

}

void BehaviourSystem::Update()
{
	RefreshView();
	for (ecs::EntityId entityId : _view)
	{
		_view.get<std::unique_ptr<BehaviourScript>>(entityId)->OnUpdate();
	}
}