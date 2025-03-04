#pragma once

#include "Collider.hpp"

namespace Physics
{
	class CircleCollider : public Collider
	{
	public:
		CircleCollider(const PhysicsWorld& world, Transform& transform);
	};
}