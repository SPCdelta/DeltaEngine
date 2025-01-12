#include "CircleCollider.hpp"

Physics::CircleCollider::CircleCollider(const PhysicsWorld& world, Transform& transform)
	: Collider(world, transform, Physics::ShapeType::CIRCLE)
{

}