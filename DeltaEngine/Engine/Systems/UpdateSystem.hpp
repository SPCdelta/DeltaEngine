#pragma once

#include "../Ecs/Registry.hpp"
#include "../Transform.hpp"
#include "../BehaviourScript.hpp"

class UpdateSystem : public ecs::System<Transform, BehaviourScript*>
{
public:
	UpdateSystem(ecs::View<Transform, BehaviourScript*> view)
		: ecs::System<Transform, BehaviourScript*>(view)
	{

	}

	~UpdateSystem()
	{
		for (ecs::EntityId entityId : _view)
		{
			delete _view.get<BehaviourScript*>(entityId);
		}
	}

	void OnStart()
	{
		//for (ecs::EntityId entityId : _view)
		//{
		//	_view.get<BehaviourScript*>(entityId)->OnStart();
		//}
	}

	void Update()
	{
		for (ecs::EntityId entityId : _view)
		{
			_view.get<BehaviourScript*>(entityId)->OnUpdate();
		}
	}
};