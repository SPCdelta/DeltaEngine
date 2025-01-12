#include "BoxCollider.hpp"

Physics::BoxCollider::BoxCollider(const PhysicsWorld& world, Transform& transform)
	: Collider(world, transform, Physics::ShapeType::BOX)
{

}