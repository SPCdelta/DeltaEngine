#pragma once

#include "../Ecs/Registry.hpp"
#include "../Transform.hpp"
#include "../Core/Despawner.hpp"

class DespawnSystem : public ecs::System<Transform, Despawner>
{
public:
	DespawnSystem(ecs::View<Transform, Despawner> view)
		: ecs::System<Transform, Despawner>(view)
	{

	}

	void Update()
	{
		for (ecs::EntityId entityId : _view)
		{
			Despawner& despawner = _view.get<Despawner>(entityId);
			if (despawner._timer <= 0.0f)
			{
				Transform& transform = _view.get<Transform>(entityId);
				transform.gameObject->Destroy(transform.gameObject);
			}
			else
			{
				despawner._timer -= Time::GetDeltaTime(); 
			}
		}
	}
};