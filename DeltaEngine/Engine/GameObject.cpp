#include "GameObject.hpp"
#include "Scene/Scene.hpp"

GameObject::GameObject(
	Scene* scene,
	ecs::Registry& reg, 
	Physics::PhysicsWorld& physicsWorld, 
	Events::EventDispatcher<const std::string&>& changeScene,
	Camera* camera, Transform newTransform)
	: _reg(reg), 
	_physicsWorld{ physicsWorld },
	_changeScene{ changeScene },
	_camera{ camera },
	_scene{ scene }
{
	_id = reg.CreateEntity();
	transform = &_reg.AddComponent<Transform>(_id, newTransform);
	transform->gameObject = this;
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