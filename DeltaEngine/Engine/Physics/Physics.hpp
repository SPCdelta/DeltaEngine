#pragma once

#include <stdint.h>

#include <box2d/box2d.h>

#include "../Core/Math/Vector2.hpp"
#include "../Core/Events/EventDispatcher.hpp"

#include "../Transform.hpp"


namespace Physics
{
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

	struct PhysicsShape
	{
		Shape shape; // _b2shapeDef
		PhysicsId id; // _b2shapeId
	};

	static bool AreEqual(const Physics::PhysicsId id1, const Physics::PhysicsId id2)
	{
		return
			id1.index1 == id2.index1 &&
			id1.revision == id2.revision &&
			id1.world0 == id2.world0;
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

	namespace Facade
	{
		static WorldId ToWorldId(b2WorldId worldId)
		{
			return { worldId.index1, worldId.revision };
		}

		static PhysicsId ToPhysicsId(b2BodyId bodyId)
		{
			return { bodyId.index1, bodyId.world0, bodyId.revision };
		}

		static PhysicsId ToPhysicsId(b2ShapeId shapeId)
		{
			return { shapeId.index1, shapeId.world0, shapeId.revision };
		}
	}
}