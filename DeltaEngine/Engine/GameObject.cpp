#include "GameObject.hpp"

GameObject::GameObject(ecs::Registry& reg, Transform newTransform) : _reg(reg)
{
	_id = reg.CreateEntity();
	transform = &_reg.AddComponent<Transform>(_id, newTransform);
}

GameObject::~GameObject()
{

}