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

	class Rigidbody
	{
	public:
		Rigidbody(const Collider& collider)
			: _collider{ collider }
		{

		}

		void SetType(RigidbodyType type)
		{
			b2Body_SetType(_collider._b2bodyId, static_cast<b2BodyType>(type));
		}

		RigidbodyType GetType()
		{
			return static_cast<RigidbodyType>(b2Body_GetType(_collider._b2bodyId));
		}

		void AddForce(Math::Vector2 force, ForceMode forceMode)
		{
			b2Vec2 b2Force(force.x, force.y);

			switch (forceMode)
			{
				case ForceMode::ACCELERATE:
					b2Body_ApplyForceToCenter(_collider._b2bodyId, b2Force, true);
					break;
				case ForceMode::IMPULSE:
					b2Body_ApplyLinearImpulseToCenter(_collider._b2bodyId, b2Force, true);
					break;
			}
		}

		void SetVelocity(Math::Vector2 velocity)
		{
			b2Vec2 b2Velocity(velocity.x, velocity.y);
			b2Body_SetLinearVelocity(_collider._b2bodyId, b2Velocity);
		}

		const Math::Vector2 GetVelocity() const
		{
			b2Vec2 b2Velocity = b2Body_GetLinearVelocity(_collider._b2bodyId);
			return Math::Vector2(b2Velocity.x, b2Velocity.y);
		}

		void SetGravityScale(float gravityScale)
		{
			b2Body_SetGravityScale(_collider._b2bodyId, gravityScale);
		}

		float GetGravityScale()
		{
			return b2Body_GetGravityScale(_collider._b2bodyId);
		}

	private:
		const Collider _collider;

		float _mass{ 1.0f };
	};
}