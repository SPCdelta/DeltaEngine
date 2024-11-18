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

		void Update()
		{
			// Order is very important here
			_physicsWorld.Update();
			std::vector<TestData>& triggers{ _physicsWorld.GetCurrentTriggers() };

			for (ecs::EntityId entityId : _view)
			{
				// Check for Trigger collision
				Rigidbody& rb{ _view.get<Rigidbody>(entityId) };

				{
					b2Vec2 position = b2Body_GetPosition(rb.GetCollider()._bodyId);
					rb.GetCollider()._transform.position.SetX(position.x);
					rb.GetCollider()._transform.position.SetY(position.y);
				}
				
				for (TestData& trigger : triggers)
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

			}
		}

	private:
		PhysicsWorld& _physicsWorld;
		std::shared_ptr<CollisionSystem> _collisionSystem;
	};
}