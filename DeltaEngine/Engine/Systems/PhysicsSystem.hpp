#pragma once

#include "../Transform.hpp"
#include "../Physics/Rigidbody.hpp"
#include "CollisionSystem.hpp"

namespace Physics
{
	class PhysicsSystem : public ecs::System<Transform, Rigidbody>
	{
	public:
		PhysicsSystem(ecs::View<Transform, Rigidbody> view, ecs::Registry& reg, PhysicsWorld& physicsWorld);

		void TransformToBox2D();
		void Box2DToTransform();

		void ApplyPhysics();
		void PhysicsEvents();

	private:
		PhysicsWorld& _physicsWorld;
		std::shared_ptr<CollisionSystem> _collisionSystem;
	};
}