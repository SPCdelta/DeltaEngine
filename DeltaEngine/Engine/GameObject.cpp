#include "GameObject.hpp"
#include "Scene/Scene.hpp"

GameObject::GameObject(
	Scene* scene, ecs::EntityId id, ecs::Registry& reg, Physics::PhysicsWorld& physicsWorld, 
	Events::EventDispatcher<const std::string&>& changeScene, Camera* camera, Transform& transform_)
	: _reg(reg), 
	  _physicsWorld{ physicsWorld },
	  _changeScene{ changeScene },
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

std::shared_ptr<GameObject> GameObject::Instantiate()
{
	return _scene->Instantiate();
}

void GameObject::Destroy(GameObject* toDestroy)
{
	_scene->DestroyObject(toDestroy);
}

void GameObject::Destroy(std::shared_ptr<GameObject> toDestroy)
{
	_scene->DestroyObject(toDestroy);
}