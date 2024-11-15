#include "GameObject.hpp"

GameObject::GameObject(ecs::Registry& reg) : _reg(reg)
{
	_id = reg.CreateEntity();
	transform = &_reg.AddComponent<Transform>(_id, Transform({0.0f, 0.0f}, 0.0f, {1.0f, 1.0f}));
}

GameObject::~GameObject()
{

}