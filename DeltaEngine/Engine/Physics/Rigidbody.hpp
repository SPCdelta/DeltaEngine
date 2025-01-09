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
			EnginePhysics::SetBodyType(_collider._bodyId, RigidbodyType::DYNAMIC_BODY);
			EnginePhysics::EnableSleep(collider._bodyId, false);
		}

		~Rigidbody()
		{
			EnginePhysics::DestroyRigidbody();
		}

		Events::EventDispatcher<Collider&> onTriggerEnter{};
		Events::EventDispatcher<Collider&> onTriggerExit{};
		Events::EventDispatcher<Collider&> onCollisionEnter{};
		Events::EventDispatcher<Collider&> onCollisionExit{};

		const EnginePhysics::PhysicsShape& GetShape() const { return _collider._shape; }

		void SetType(RigidbodyType type) { EnginePhysics::SetBodyType(_collider._bodyId, type); }
		RigidbodyType GetType() const { return EnginePhysics::GetBodyType(_collider._bodyId); }

		Collider& GetCollider() const { return _collider; }

		void AddForce(Math::Vector2 force, ForceMode forceMode) { EnginePhysics::AddForce(_collider._bodyId, force, forceMode); }

		void SetVelocity(Math::Vector2 velocity) { EnginePhysics::SetVelocity(_collider._bodyId, velocity); }
		const Math::Vector2 GetVelocity() const { return EnginePhysics::GetVelocity(_collider._bodyId); }

		void SetGravityScale(float gravityScale) { EnginePhysics::SetGravityScale(_collider._bodyId, gravityScale); }
		float GetGravityScale() const { return EnginePhysics::GetGravityScale(_collider._bodyId); }

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