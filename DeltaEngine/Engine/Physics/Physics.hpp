#pragma once

#include <stdint.h>

#include <box2d/box2d.h>

#include "../Core/Math/Vector2.hpp"
#include "../Core/Events/EventDispatcher.hpp"

#include "../Transform.hpp"


namespace Physics
{
	constexpr float TIME_STEP = (1.0f / 60.0f);
	constexpr int SUB_STEP_COUNT = 4;

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

	struct PhysicsId
	{
		int32_t index1;
		uint16_t world0;
		uint16_t revision;

		operator b2BodyId() const { return b2BodyId{ index1, world0, revision }; }
		operator b2ShapeId() const { return b2ShapeId{ index1, world0, revision }; }
	};

	using World = b2WorldDef;

	struct WorldId
	{
		uint16_t index1;
		uint16_t revision;

		operator b2WorldId() const
		{
			return b2WorldId{ index1, revision };
		}
	};

	struct WorldData
	{
		WorldId id;
		World world;
	};

	using PhysicsBody = b2BodyDef;
	using PhysicsPolygon = b2Polygon;
	using Shape = b2ShapeDef;

	using CollisionEvents = b2ContactEvents;
	using CollisionTouchStartEvent = b2ContactBeginTouchEvent;
	using CollisionTouchEndEvent = b2ContactEndTouchEvent;

	using TriggerEvents = b2SensorEvents;
	using TriggerTouchStartEvent = b2SensorBeginTouchEvent;
	using TriggerTouchEndEvent = b2SensorEndTouchEvent;

	struct PhysicsShape
	{
		Shape shape; // _b2shapeDef
		PhysicsId id; // _b2shapeId
	};

	inline bool AreEqual(const PhysicsId id1, const PhysicsId id2)
	{
		return
			id1.index1 == id2.index1 &&
			id1.revision == id2.revision &&
			id1.world0 == id2.world0;
	}

	static WorldId ToWorldId(b2WorldId worldId)
	{
		return {worldId.index1, worldId.revision};
	}

	static PhysicsId ToPhysicsId(b2BodyId bodyId)
	{
		return {bodyId.index1, bodyId.world0, bodyId.revision};
	}

	static PhysicsId ToPhysicsId(b2ShapeId shapeId)
	{
		return {shapeId.index1, shapeId.world0, shapeId.revision};
	}

	//
	inline Shape DefaultShape()
	{
		return b2DefaultShapeDef();
	}
	inline PhysicsBody DefaultBody()
	{
		return b2DefaultBodyDef();
	}

	inline WorldData CreateWorld()
	{
		WorldData data{};
		data.world = b2DefaultWorldDef();
		data.id = Physics::ToWorldId(b2CreateWorld(&data.world));
		return data;
	}

	inline PhysicsId CreateBody(WorldId worldId, PhysicsBody* physicsBody)
	{
		return Physics::ToPhysicsId(b2CreateBody(worldId, physicsBody));
	}

	inline PhysicsPolygon CreateBox(const Math::Vector2& scale)
	{
		return b2MakeBox(scale.GetX() / 2.0f, scale.GetY() / 2.0f);
	}

	inline PhysicsPolygon CreateCircle(const Math::Vector2& scale)
	{
		return b2MakeBox(scale.GetX() / 2.0f, scale.GetY() / 2.0f);
	}

	inline PhysicsId CreatePolygonShape(PhysicsId bodyId, const PhysicsShape* shape, const PhysicsPolygon* polygon)
	{
		return Physics::ToPhysicsId(b2CreatePolygonShape(bodyId, &shape->shape, polygon));
	}

	inline void SetBodyType(PhysicsId bodyId, RigidbodyType type)
	{
		b2Body_SetType(bodyId, static_cast<b2BodyType>(RigidbodyType::DYNAMIC_BODY));
	}
	inline RigidbodyType GetBodyType(PhysicsId bodyId)
	{
		return static_cast<RigidbodyType>(b2Body_GetType(bodyId));
	}

	inline void SetVelocity(PhysicsId bodyId, const Math::Vector2& velocity)
	{
		b2Vec2 b2Velocity(velocity.GetX(), velocity.GetY());
		b2Body_SetLinearVelocity(bodyId, b2Velocity);
	}
	inline Math::Vector2 GetVelocity(PhysicsId bodyId)
	{
		b2Vec2 b2Velocity = b2Body_GetLinearVelocity(bodyId);
		return Math::Vector2(b2Velocity.x, b2Velocity.y);
	}

	inline void SetGravityScale(PhysicsId bodyId, float gravityScale)
	{
		b2Body_SetGravityScale(bodyId, gravityScale);
	}
	inline float GetGravityScale(const PhysicsId bodyId)
	{
		return b2Body_GetGravityScale(bodyId);
	}

	inline void AddForce(PhysicsId bodyId, const Math::Vector2& force, ForceMode forceMode)
	{
		b2Vec2 b2Force(force.GetX(), force.GetY());

		switch (forceMode)
		{
			case ForceMode::ACCELERATE:
				b2Body_ApplyForceToCenter(bodyId, b2Force, true);
				break;
			case ForceMode::IMPULSE:
				b2Body_ApplyLinearImpulseToCenter(bodyId, b2Force, true);
				break;
		}
	}

	inline Math::Vector2 GetPosition(PhysicsId bodyId)
	{
		b2Vec2 b2Pos = b2Body_GetPosition(bodyId);
		return Math::Vector2(b2Pos.x, b2Pos.y);
	}

	inline void DestroyShape(PhysicsId shapeId)
	{
		b2DestroyShape(shapeId);
	}

	inline void DestroyWorld(WorldId id)
	{
		b2DestroyWorld(static_cast<b2WorldId>(id));
	}

	inline void AdvancePhysics(WorldId id, float time, int subSteps)
	{
		b2World_Step(id, time, subSteps);
	}

	inline CollisionEvents GetCollisionEvents(WorldId id)
	{
		return b2World_GetContactEvents(id);
	}

	inline TriggerEvents GetTriggerEvents(WorldId id)
	{
		return b2World_GetSensorEvents(id);
	}

	namespace Event
	{
		//class CollisionEventData : public Events::Event
		//{
		//public:
		//	CollisionEventData()
		//	{

		//	}
		//};

		class SensorEventData : public Events::Event
		{
		public:
			SensorEventData(PhysicsShape shape)
				: _shape{ shape }
			{ }

			PhysicsShape GetShape() const
			{
				return _shape;
			}

		private:
			PhysicsShape _shape;
		};
	}
}