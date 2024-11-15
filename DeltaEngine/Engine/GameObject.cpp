#include "GameObject.hpp"

GameObject::GameObject(ecs::Registry& reg) : _reg(reg), sprite(nullptr)
{
	_id = reg.CreateEntity();
	transform = &_reg.AddComponent<Transform>(_id, Transform({ 10.0f, 10.0f }, 0.0f, { 64.0f, 64.0f }));
}

GameObject::~GameObject()
{
	delete sprite;
	sprite = nullptr;

	delete transform;
	transform = nullptr;
}