#pragma once

#include "../Ecs/Include.hpp"
#include "../Transform.hpp"
#include "../BehaviourScript.hpp"

//class UpdateSystem : public ecs::System<Transform, BehaviourScript*>
//{
//public:
//	UpdateSystem(ecs::View<Transform, BehaviourScript*> view)
//		: ecs::System<Transform, BehaviourScript*>(view)
//	{
//
//	}
//
//	~UpdateSystem()
//	{
//		for (ecs::EntityId entityId : _view)
//		{
//			delete _view.get<BehaviourScript*>(entityId);
//		}
//	}
//
//	void Update()
//	{
//		for (ecs::EntityId entityId : _view)
//		{
//			_view.get<BehaviourScript*>(entityId)->OnUpdate();
//		}
//	}
//};

class BehaviourSystem : public ecs::System<std::unique_ptr<BehaviourScript>>
{
public:
	BehaviourSystem(ecs::Registry& reg)
		: ecs::System<std::unique_ptr<BehaviourScript>>(reg)
	{

	}

	void Update()
	{
		//RefreshView();
		for (ecs::EntityId entityId : _view)
		{
			_view.get<std::unique_ptr<BehaviourScript>>(entityId)->OnUpdate();
		}
	}
};