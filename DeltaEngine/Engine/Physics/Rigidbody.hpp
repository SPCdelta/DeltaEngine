#pragma once

#include "Physics.hpp"
#include "Collider.hpp"

namespace Physics
{
	class PhysicsSystem;

	class Rigidbody
	{
	public:
		Rigidbody(Collider& collider);
		~Rigidbody();

		Events::EventDispatcher<Collider&> onTriggerEnter{};
		Events::EventDispatcher<Collider&> onTriggerExit{};
		Events::EventDispatcher<Collider&> onCollisionEnter{};
		Events::EventDispatcher<Collider&> onCollisionExit{};

		const EnginePhysics::PhysicsShape& GetShape() const;

		void SetType(RigidbodyType type);
		RigidbodyType GetType() const;

		Collider& GetCollider() const;

		void AddForce(Math::Vector2 force, ForceMode forceMode);

		void SetVelocity(Math::Vector2 velocity);
		const Math::Vector2 GetVelocity() const;

		void SetGravityScale(float gravityScale);
		float GetGravityScale() const;

		float GetSpeed() const;

	private:
		Collider& _collider;

		float _mass{ 1.0f };
	};
}