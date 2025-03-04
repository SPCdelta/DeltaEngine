#include "PhysicsSystem.hpp"

Physics::PhysicsSystem::PhysicsSystem(ecs::Registry& reg, PhysicsWorld& physicsWorld)
	: ecs::System<Transform, Rigidbody>(reg), 
	  _physicsWorld{ physicsWorld }
{
	_collisionSystem = reg.CreateSystem<CollisionSystem, std::unique_ptr<Collider>>();
}

void Physics::PhysicsSystem::TransformToBox2D()
{
	RefreshView();
	for (ecs::EntityId entityId : _view)
	{
		Rigidbody& rb = _view.get<Rigidbody>(entityId);
		EnginePhysics::SetPosition(rb.GetShape().id, rb.GetCollider().transform.position);
	}
}

void Physics::PhysicsSystem::Box2DToTransform()
{
	RefreshView();
	for (ecs::EntityId entityId : _view)
	{
		Rigidbody& rb = _view.get<Rigidbody>(entityId);
		Math::Vector2 position = EnginePhysics::GetPosition(rb.GetCollider()._bodyId);
		rb.GetCollider().transform.position.Set(position);
	}
}

void Physics::PhysicsSystem::ApplyPhysics()
{ 
	_physicsWorld.Update();
}

void Physics::PhysicsSystem::PhysicsEvents()
{
	RefreshView();
	std::vector<CollisionData>& triggers{ _physicsWorld.GetCurrentTriggers() };
	std::vector<CollisionData>& collisions{ _physicsWorld.GetCurrentCollisions() };

	for (ecs::EntityId entityId : _view)
	{
		// Check for Trigger collision
		Rigidbody& rb{ _view.get<Rigidbody>(entityId) };
		
		// Check for Trigger Collision
		for (CollisionData& trigger : triggers)
		{
			// Check if Trigger has our Collider
			EnginePhysics::PhysicsId otherId;
			if (EnginePhysics::AreEqual(rb.GetShape().id, trigger.shape1))
				otherId = trigger.shape2;
			else if (EnginePhysics::AreEqual(rb.GetShape().id, trigger.shape2))
				otherId = trigger.shape1;
			else // If not this Rb doesnt have it
				continue;

			// Find Collider with ShapeId of other Collider
			Collider* collider{ _collisionSystem->GetCollider(otherId) };
			if (!collider) continue;

			// Send Event based on type
			if (trigger.state == Physics::CollisionState::ENTER)
				rb.onTriggerEnter.Dispatch(*collider);
			else
				rb.onTriggerExit.Dispatch(*collider);
		}

		// Check for Contact Collision
		for (CollisionData& collision : collisions)
		{
			// Check if Collision has our Collider
			EnginePhysics::PhysicsId otherId;
			if (EnginePhysics::AreEqual(rb.GetShape().id, collision.shape1))
				otherId = collision.shape2;
			else if (EnginePhysics::AreEqual(rb.GetShape().id, collision.shape2))
				otherId = collision.shape1;
			else // If not this Rb doesnt have it	
				continue;

			// Find Collider with ShapeId of other Collider
			Collider* collider{ _collisionSystem->GetCollider(otherId) };
			if (!collider) continue;

			// Send Event based on type
			if (collision.state == Physics::CollisionState::ENTER)
				rb.onCollisionEnter.Dispatch(*collider);
			else
				rb.onCollisionExit.Dispatch(*collider);
		}
	}
}