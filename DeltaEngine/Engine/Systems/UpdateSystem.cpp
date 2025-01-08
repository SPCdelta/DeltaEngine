#include "UpdateSystem.hpp"

UpdateSystem::UpdateSystem(ecs::View<Transform, BehaviourScript*> view)
	: ecs::System<Transform, BehaviourScript*>(view)
{

}

UpdateSystem::~UpdateSystem()
{
	for (ecs::EntityId entityId : _view)
	{
		delete _view.get<BehaviourScript*>(entityId);
	}
}

void UpdateSystem::Update()
{
	for (ecs::EntityId entityId : _view)
	{
		_view.get<BehaviourScript*>(entityId)->OnUpdate();
	}
}