#pragma once

#include <optional>

#include "../Ecs/Registry.hpp"
#include "../Physics/Collider.hpp"

namespace Physics
{
	class CollisionSystem : public ecs::System<Collider*>
	{
	public:
		CollisionSystem(ecs::View<Collider*> view);
		~CollisionSystem();

		Collider* GetCollider(EnginePhysics::PhysicsId id);
	};
}