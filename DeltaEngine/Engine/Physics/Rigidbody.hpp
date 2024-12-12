#pragma once

#include "Physics.hpp"
#include "Collider.hpp"

namespace Physics
{
	class PhysicsSystem;

	class Rigidbody
	{
	public:
		Rigidbody(Collider& collider)
			: _collider{ collider }
		{
			Physics::SetBodyType(_collider._bodyId, RigidbodyType::DYNAMIC_BODY);
			b2Body_EnableSleep(collider._bodyId, false);
		}

		Events::EventDispatcher<Collider&> onTriggerEnter{};
		Events::EventDispatcher<Collider&> onTriggerExit{};
		Events::EventDispatcher<Collider&> onCollisionEnter{};
		Events::EventDispatcher<Collider&> onCollisionExit{};

		const PhysicsShape& GetShape() const { return _collider._shape; }

		void SetType(RigidbodyType type) { Physics::SetBodyType(_collider._bodyId, type); }
		RigidbodyType GetType() const { return Physics::GetBodyType(_collider._bodyId); }

		Collider& GetCollider() const { return _collider; }

		void AddForce(Math::Vector2 force, ForceMode forceMode) { Physics::AddForce(_collider._bodyId, force, forceMode); }

		void SetVelocity(Math::Vector2 velocity) { Physics::SetVelocity(_collider._bodyId, velocity); }
		const Math::Vector2 GetVelocity() const { return Physics::GetVelocity(_collider._bodyId); }

		void SetGravityScale(float gravityScale) { Physics::SetGravityScale(_collider._bodyId, gravityScale); }
		float GetGravityScale() const { return Physics::GetGravityScale(_collider._bodyId); }

		float GetSpeed() const 
		{
			Math::Vector2 velocity = GetVelocity();
			return std::abs(velocity.GetX()) + std::abs(velocity.GetY());
		}

	private:
		Collider& _collider;

		float _mass{ 1.0f };
	};
}