#pragma once

#include <optional>

#include "../Ecs/Include.hpp"
#include "../Physics/Collider.hpp"

namespace Physics
{
	// This will NOT work due to BoxCollider and CircleCollider their inheritance not
	// being of the same base type for the ecs, do the same as done for behaviourscript to make it work
	class CollisionSystem : public ecs::System<std::unique_ptr<Collider>>
	{
	public:
		CollisionSystem(ecs::Registry& reg)
			: ecs::System<std::unique_ptr<Collider>>(reg)
		{

		}

		Collider* GetCollider(EnginePhysics::PhysicsId id)
		{
			RefreshView();

			for (ecs::EntityId entityId : _view)
			{
				std::unique_ptr<Collider>& collider = _view.get<std::unique_ptr<Collider>>(entityId);
				if (EnginePhysics::AreEqual(collider->_shape.id, id))
				{
					return collider.get();
				}
			}

			return nullptr;
		}
	};
}