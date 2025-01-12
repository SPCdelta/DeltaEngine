#include "Rigidbody.hpp"

Physics::Rigidbody::Rigidbody(Collider& collider) 
	: _collider{collider}
{
	EnginePhysics::SetBodyType(_collider._bodyId, RigidbodyType::DYNAMIC_BODY);
	EnginePhysics::EnableSleep(collider._bodyId, false);
}

Physics::Rigidbody::~Rigidbody()
{
	EnginePhysics::DestroyRigidbody();
}

const EnginePhysics::PhysicsShape& Physics::Rigidbody::GetShape() const
{
	return _collider._shape;
}

void Physics::Rigidbody::SetType(RigidbodyType type)
{
	EnginePhysics::SetBodyType(_collider._bodyId, type);
}

Physics::RigidbodyType Physics::Rigidbody::GetType() const
{
	return EnginePhysics::GetBodyType(_collider._bodyId);
}

Physics::Collider& Physics::Rigidbody::GetCollider() const
{
	return _collider;
}

void Physics::Rigidbody::AddForce(Math::Vector2 force, ForceMode forceMode)
{
	EnginePhysics::AddForce(_collider._bodyId, force, forceMode);
}

void Physics::Rigidbody::SetVelocity(Math::Vector2 velocity)
{
	EnginePhysics::SetVelocity(_collider._bodyId, velocity);
}

const Math::Vector2 Physics::Rigidbody::GetVelocity() const
{
	return EnginePhysics::GetVelocity(_collider._bodyId);
}

void Physics::Rigidbody::SetGravityScale(float gravityScale)
{
	EnginePhysics::SetGravityScale(_collider._bodyId, gravityScale);
}

float Physics::Rigidbody::GetGravityScale() const
{
	return EnginePhysics::GetGravityScale(_collider._bodyId);
}

float Physics::Rigidbody::GetSpeed() const
{
	Math::Vector2 velocity = GetVelocity();
	return std::abs(velocity.GetX()) + std::abs(velocity.GetY());
}
