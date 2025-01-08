#pragma once

#include <optional>

#include "../Ecs/Registry.hpp"
#include "../Physics/Collider.hpp"

namespace Physics
{
	// TODO keep this comment?
	// This will NOT work due to BoxCollider and CircleCollider their inheritance not
	// being of the same base type for the ecs, do the same as done for behaviourscript to make it work
	class CollisionSystem : public ecs::System<Collider*>
	{
	public:
		CollisionSystem(ecs::View<Collider*> view);
		~CollisionSystem();

		Collider* GetCollider(EnginePhysics::PhysicsId id);
	};
}