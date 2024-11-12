#pragma once

#include <stdint.h>

#include <box2d/box2d.h>

#include "../Core/Math/Vector2.hpp"

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