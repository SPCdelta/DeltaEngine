#include "GameObject.hpp"

GameObject::GameObject(ecs::Registry& reg, const char* spritePath) : _reg(reg)
{
	_id = reg.CreateEntity();
	transform = &_reg.AddComponent<Transform>(_id, Transform({ 10.0f, 10.0f }, 0.0f, { 64.0f, 64.0f }));
	sprite = &_reg.AddComponent<Sprite>(_id, Sprite(spritePath));
}
