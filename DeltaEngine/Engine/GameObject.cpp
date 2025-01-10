#include "GameObject.hpp"
#include "Scene/Scene.hpp"

GameObject::GameObject(
	Scene* scene, ecs::EntityId id, ecs::Registry& reg, Physics::PhysicsWorld& physicsWorld, 
	Camera* camera, Transform& transform_)
	: _reg(reg), 
	  _physicsWorld{ physicsWorld },
	  _camera{ camera },
	  _scene{ scene },
	  _id{ id },
	  transformRef{ transform_ },
	  transform{ &transform_ }
{
	
}

GameObject::~GameObject()
{

}

void GameObject::LoadScene(const std::string& name)
{
	_scene->LoadScene(name);
}

std::shared_ptr<GameObject> GameObject::Instantiate()
{
	return _scene->Instantiate();
}

std::shared_ptr<GameObject> GameObject::Instantiate(Transform transform)
{
	return _scene->Instantiate(transform);
}