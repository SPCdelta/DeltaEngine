#pragma once

#include "Physics.hpp"
#include "Collider.hpp"

namespace Physics
{
	enum class RigidbodyType
	{
		STATIC_BODY = 0,
		KINEMATIC_BODY = 1,
		DYNAMIC_BODY = 2
	};

	enum class ForceMode
	{
		ACCELERATE = 0,
		IMPULSE = 1,
	};

	class PhysicsSystem;

	// TODO: to much b2... here
	class Rigidbody
	{
	public:
		Rigidbody(Collider& collider)
			: _collider{ collider }
		{
			b2Body_SetType(_collider._bodyId, static_cast<b2BodyType>(RigidbodyType::DYNAMIC_BODY));
		}

		Events::EventDispatcher<Collider&> onTriggerEnter{};
		Events::EventDispatcher<Collider&> onTriggerExit{};
		Events::EventDispatcher<Collider&> onCollisionEnter{};
		Events::EventDispatcher<Collider&> onCollisionExit{};

		const PhysicsShape& GetShape() const { return _collider._shape; }

		void SetType(RigidbodyType type)
		{
			b2Body_SetType(_collider._bodyId, static_cast<b2BodyType>(type));
		}

		RigidbodyType GetType() const
		{
			return static_cast<RigidbodyType>(b2Body_GetType(_collider._bodyId));
		}

		Collider& GetCollider() const
		{
			return _collider;
		}

		void AddForce(Math::Vector2 force, ForceMode forceMode)
		{
			b2Vec2 b2Force(force.GetX(), force.GetY());

			switch (forceMode)
			{
				case ForceMode::ACCELERATE:
					b2Body_ApplyForceToCenter(_collider._bodyId, b2Force, true);
					break;
				case ForceMode::IMPULSE:
					b2Body_ApplyLinearImpulseToCenter(_collider._bodyId, b2Force, true);
					break;
			}
		}

		void SetVelocity(Math::Vector2 velocity)
		{
			b2Vec2 b2Velocity(velocity.GetX(), velocity.GetY());
			b2Body_SetLinearVelocity(_collider._bodyId, b2Velocity);
		}

		const Math::Vector2 GetVelocity() const
		{
			b2Vec2 b2Velocity = b2Body_GetLinearVelocity(_collider._bodyId);
			return Math::Vector2(b2Velocity.x, b2Velocity.y);
		}

		void SetGravityScale(float gravityScale)
		{
			b2Body_SetGravityScale(_collider._bodyId, gravityScale);
		}

		float GetGravityScale() const
		{
			return b2Body_GetGravityScale(_collider._bodyId);
		}

	private:
		Collider& _collider;

		float _mass{ 1.0f };
	};
}