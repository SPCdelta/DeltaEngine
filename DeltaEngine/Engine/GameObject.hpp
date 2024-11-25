#pragma once

#include <vector>
#include <type_traits>

#include "Ecs/Registry.hpp"
#include "Transform.hpp"
#include "Rendering/Camera.hpp"

#include "Core/Events/EventDispatcher.hpp"

//#include "BehaviourScript.hpp"
class BehaviourScript;

#include "Physics/Collider.hpp"
#include "Physics/Rigidbody.hpp"

class GameObject
{
public:
	template <typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		if constexpr (std::is_base_of_v<BehaviourScript, T>)
		{
			T* component = static_cast<T*>(_reg.AddComponent<BehaviourScript*>(_id, new T()));
			//component->SetGameObject(this);
			component->gameObject = this;
			component->camera = _camera;
			return component;
		}
		else if constexpr (std::is_base_of_v<Physics::Collider, T>)
		{
			T* component = static_cast<T*>(_reg.AddComponent<Physics::Collider*>(_id, new T(_physicsWorld, *transform)));
			return component;
		}
		else if constexpr (std::is_same_v<T, Physics::Rigidbody>)
		{
			if (!_reg.HasComponent<Physics::Collider*>(_id))
			{
				throw std::exception("Rigidbody must have a Collider!");
			}

			return static_cast<T*>(_AddComponent<Physics::Rigidbody>(Physics::Rigidbody(*_reg.GetComponent<Physics::Collider*>(_id))));
		}
		else
		{
			return static_cast<T*>(_AddComponent<T>(T(std::forward<Args>(args)...)));
		}
	}

	template<typename T>
	void RemoveComponent()
	{
		_reg.RemoveComponent<T>(_id);
	}

	template<typename T>
	T& GetComponent()
	{
		return _reg.GetComponent<T>(_id);
	}

	ecs::EntityId GetId() const
	{ 
		return _id;
	}

	GameObject(ecs::Registry& reg, Physics::PhysicsWorld& physicsWorld, Events::EventDispatcher<const std::string&>& changeScene, Camera* camera, Transform newTransform = {{0.0f, 0.0f}, 0.0f, {1.0f, 1.0f}});
	~GameObject();

	Transform* transform = nullptr;

	bool IsActive() const { return _active; }
	bool SetActive(bool active) { _active = active; }

	// Scene
	void LoadScene(const std::string& name) { _changeScene.Dispatch(name); }

private:
	bool _active{ true };

	ecs::EntityId _id;
	ecs::Registry& _reg;
	Physics::PhysicsWorld& _physicsWorld;
	Events::EventDispatcher<const std::string&>& _changeScene;
	Camera* _camera = nullptr;

	template<typename T>
	T* _AddComponent(T component)
	{
		return &_reg.AddComponent<T>(_id, std::move(component)); 
	}
};

