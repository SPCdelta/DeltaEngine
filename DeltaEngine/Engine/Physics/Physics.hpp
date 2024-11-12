#pragma once

#include <stdint.h>

#include <box2d/box2d.h>
#include "../Core/Math/Vector2.hpp"

namespace Physics
{
	struct PhysicsId
	{
		int32_t index1;
		uint16_t world0;
		uint16_t revision;
	};

	using PhysicsBody = b2BodyDef;
	using PhysicsPolygon = b2Polygon;
	using Shape = b2ShapeDef;

	struct PhysicsShape
	{
		Shape shape; // _b2shapeDef
		PhysicsId id; // _b2shapeId
	};
}