#pragma once

#include <optional>

#include "../Ecs/Registry.hpp"
#include "../Physics/Collider.hpp"

namespace Physics
{
	// This will NOT work due to BoxCollider and CircleCollider their inheritance not
	// being of the same base type for the ecs, do the same as done for behaviourscript to make it work
	class CollisionSystem : public ecs::System<Collider*>
	{
	public:
		CollisionSystem(ecs::View<Collider*> view)
			: ecs::System<Collider*>(view)
		{

		}

		~CollisionSystem()
		{
			for (ecs::EntityId entityId : _view)
			{
				delete _view.get<Collider*>(entityId);
			}
		}

		Collider* GetCollider(Physics::PhysicsId id)
		{
			for (ecs::EntityId entityId : _view)
			{
				Collider* collider{ _view.get<Collider*>(entityId) };
				if (Physics::AreEqual(collider->_shape.id, id))
				{
					return collider;
				}
			}

			return nullptr;
		}
	};
}