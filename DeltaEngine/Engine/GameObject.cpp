#include "GameObject.hpp"

GameObject::GameObject(ecs::Registry& reg) : _reg(reg)
{
	_id = reg.CreateEntity();
}

GameObject::~GameObject()
{

}