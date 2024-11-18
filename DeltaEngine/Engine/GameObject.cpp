#include "GameObject.hpp"

GameObject::GameObject(ecs::Registry& reg, Physics::PhysicsWorld& physicsWorld,
					   Transform newTransform)
	: _reg(reg), _physicsWorld{ physicsWorld }
{
	_id = reg.CreateEntity();
	transform = &_reg.AddComponent<Transform>(_id, newTransform);
}

GameObject::~GameObject()
{

}