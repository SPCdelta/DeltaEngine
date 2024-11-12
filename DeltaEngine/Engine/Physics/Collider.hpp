#pragma once

#include "Physics.hpp"

namespace Physics
{
	class Collider
	{
	public:
		Collider()
		{

		}

		PhysicsId GetColliderId() const
		{
			return _bodyId;
		}

	private:
		PhysicsBody _physicsBody; // _b2bodyDef
		PhysicsId _bodyId; // _b2bodyId
		PhysicsPolygon _polygon; // _b2polygon
		PhysicsShape _shape; 
	};
}