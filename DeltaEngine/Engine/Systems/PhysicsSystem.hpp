#pragma once

#include "../Transform.hpp"
#include "../Physics/Rigidbody.hpp"

#include "CollisionSystem.hpp"

namespace Physics
{
	class PhysicsSystem : public ecs::System<Transform, Rigidbody>
	{
	public:
		PhysicsSystem(ecs::View<Transform, Rigidbody> view, ecs::Registry& reg, PhysicsWorld& physicsWorld)
			: ecs::System<Transform, Rigidbody>(view), _physicsWorld{ physicsWorld }
		{
			_collisionSystem = reg.CreateSystem<CollisionSystem, Collider*>();
		}

		// Order is very important here
		void BeforeBehaviourUpdate()
		{ 
			_physicsWorld.Update();

			std::vector<CollisionData>& triggers{ _physicsWorld.GetCurrentTriggers() };
			std::vector<CollisionData>& collisions{ _physicsWorld.GetCurrentCollisions() };

			for (ecs::EntityId entityId : _view)
			{
				// Check for Trigger collision
				Rigidbody& rb{ _view.get<Rigidbody>(entityId) };

				// Sync Visually*
				{
					Math::Vector2 position = Physics::GetPosition(rb.GetCollider()._bodyId);
					rb.GetCollider().transform.position.SetX(position.GetX());
					rb.GetCollider().transform.position.SetY(position.GetY());
				}
				
				// Check for Trigger Collision
				for (CollisionData& trigger : triggers)
				{
					if (Physics::AreEqual(rb.GetShape().id, trigger.rbShapeId))
					{
						// Find Collider with ShapeId of Trigger Collider
						Collider* collider{ _collisionSystem->GetCollider(trigger.colliderShapeId) };
						if (!collider) continue;

						// Send Event based on type
						if (trigger.state == Physics::CollisionState::ENTER)
						{
							rb.onTriggerEnter.Dispatch(*collider);
						}
						else
						{
							rb.onTriggerExit.Dispatch(*collider);
						}
					}
				}

				// Check for Contact Collision
				for (CollisionData& collision : collisions)
				{
					if (Physics::AreEqual(rb.GetShape().id, collision.rbShapeId))
					{
						// Find Collider with ShapeId of Trigger Collider
						Collider* collider{ _collisionSystem->GetCollider(collision.colliderShapeId) };
						if (!collider) continue;

						// Send Event based on type
						if (collision.state == Physics::CollisionState::ENTER)
						{
							rb.onCollisionEnter.Dispatch(*collider);
						}
						else
						{
							rb.onCollisionExit.Dispatch(*collider);
						}
					}
				}
			}
		}

		void AfterBehaviourUpdate()
		{
			// Because physics is updated before the update loop
			// physics will generally be applied every every next frame
			// this is done to allow the even catching of the events
		}

	private:
		PhysicsWorld& _physicsWorld;
		std::shared_ptr<CollisionSystem> _collisionSystem;
	};
}