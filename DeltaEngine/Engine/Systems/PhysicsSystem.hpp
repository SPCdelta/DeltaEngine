#pragma once

#include "../Ecs/Registry.hpp"

#include "../Transform.hpp"
#include "../Physics/Rigidbody.hpp"

namespace Physics
{
	class PhysicsSystem : public ecs::System<Transform, Rigidbody>
	{
	public:
		PhysicsSystem(ecs::View<Transform, Rigidbody> view, Physics::PhysicsWorld& physicsWorld)
			: ecs::System<Transform, Rigidbody>(view)
			, _physicsWorld{ physicsWorld }
		{

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
				for (TestData& trigger : triggers)
				{
					if (Physics::AreEqual(rb.GetShape().id, trigger.rbShapeId))
					{
						if (trigger.state == Physics::CollisionState::ENTER)
						{
							rb.onTriggerEnter.Dispatch(rb.GetCollider());
						}
						else
						{
							rb.onTriggerExit.Dispatch(rb.GetCollider());
						}
					}
				}

				// Check for Contact Collision

			}
		}

	private:
		PhysicsWorld& _physicsWorld;
	};
}