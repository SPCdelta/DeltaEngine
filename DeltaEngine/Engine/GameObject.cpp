#include "GameObject.hpp"

#include "Scene/Scene.hpp"

GameObject::GameObject(Scene* scene, ecs::EntityId id, ecs::Registry& reg, Physics::PhysicsWorld& physicsWorld, Camera* camera, Transform& transform_)
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

void GameObject::Destroy()
{
	_reg.DestroyEntity(_id);
}

ecs::EntityId GameObject::GetId() const
{
	return _id;
}

bool GameObject::IsActive() const
{
	return _active;
}

void GameObject::SetActive(bool active)
{
	_active = active;
}

Layer GameObject::GetLayer() const
{
	if (_reg.HasComponent<Sprite>(_id))
		return _reg.GetComponent<Sprite>(_id).GetLayer();
	return Layer::Default;
}

void GameObject::SetLayer(Layer layer)
{
	if (_reg.HasComponent<Sprite>(_id))
		_reg.GetComponent<Sprite>(_id).SetLayer(layer);
}

void GameObject::SetTag(const std::string& tag)
{
	_tag = tag;
}

const std::string& GameObject::GetTag() const
{
	return _tag;
}

Camera* GameObject::GetCamera()
{
	return _camera;
}

void GameObject::GetWalkableTiles(std::vector<Transform*>& tiles)
{
	_scene->GetWalkableTiles(tiles);
}