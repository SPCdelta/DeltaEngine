#pragma once

#include "Collider.hpp"

namespace Physics
{
	class BoxCollider : public Collider
	{
	public:
		BoxCollider(const PhysicsWorld& world, Transform& transform)
			: Collider(world, transform, Physics::ShapeType::BOX)
		{

		}
	};
}