#include "GameObject.hpp"


GameObject::GameObject(
	ecs::Registry& reg, 
	Physics::PhysicsWorld& physicsWorld, 
	Events::EventDispatcher<const std::string&>& changeScene,
	Camera* camera, Transform newTransform)
	: _reg(reg), 
	_physicsWorld{ physicsWorld },
	_changeScene{ changeScene },
	_camera{ camera }
{
	_id = reg.CreateEntity();
	transform = &_reg.AddComponent<Transform>(_id, newTransform);
}

GameObject::~GameObject()
{

}