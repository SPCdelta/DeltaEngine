#pragma once

#include <optional>

#include "../Ecs/Include.hpp"
#include "../Physics/Collider.hpp"

namespace Physics
{
	class CollisionSystem : public ecs::System<std::unique_ptr<Collider>>
	{
	public:
		CollisionSystem(ecs::Registry& reg);

		Collider* GetCollider(EnginePhysics::PhysicsId id);
	};
}