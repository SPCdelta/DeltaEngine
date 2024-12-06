#pragma once

#include <vector>
#include <type_traits>

#include "Ecs/Registry.hpp"
#include "Transform.hpp"
#include "Rendering/Camera.hpp"
#include "Rendering/Sprite.hpp"
#include "Rendering/Layer.hpp"

#include "Audio/AudioManager.hpp"
#include "Audio/AudioSource.hpp"
#include "Audio/MusicSource.hpp"
#include "Audio/SFXSource.hpp"

#include "UI/Button.hpp"

#include "Core/Events/EventDispatcher.hpp"

//#include "BehaviourScript.hpp"
class Scene;
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
			T* component = static_cast<T*>(_reg.AddPointerComponent<BehaviourScript*>(_id, new T()));
			component->gameObject = this;
			component->transform = transform;
			component->camera = _camera;
			component->OnStart();
			return component;
		}
		else if constexpr (std::is_base_of_v<Physics::Collider, T>)
		{
			T* component = static_cast<T*>(_reg.AddPointerComponent<Physics::Collider*>(_id, new T(_physicsWorld, *transform)));
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
		else if constexpr (std::is_same_v<T, Ui::Button>)
		{
			T* component = static_cast<T*>(_AddComponent<Ui::Button>(Ui::Button(transform->position, transform->scale)));
			return component;
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
		if constexpr (std::is_base_of_v<BehaviourScript, T>)
		{
			return *static_cast<T*>(_reg.GetComponent<BehaviourScript*>(_id));
		}
		else
		{
			return _reg.GetComponent<T>(_id);
		}
	}

	template<typename T>
	bool HasComponent()
	{
		return _reg.HasComponent<T>(_id);
	}

	ecs::EntityId GetId() const
	{ 
		return _id;
	}

	GameObject(ecs::Registry& reg,
				Physics::PhysicsWorld& physicsWorld,
				Events::EventDispatcher<const std::string&>& changeScene,
				Camera* camera, 
				Transform newTransform = {{0.0f, 0.0f}, 0.0f, {1.0f, 1.0f}});
	~GameObject();

	friend class Scene;

	Transform* transform = nullptr;

	bool IsActive() const { return _active; }
	bool SetActive(bool active) { _active = active; }

	Layer GetLayer() const 
	{  
		if (_reg.HasComponent<Sprite>(_id))
			return _reg.GetComponent<Sprite>(_id).GetLayer();
		return Layer::Default;
	}

	void SetLayer(Layer layer) 
	{ 
		if (_reg.HasComponent<Sprite>(_id))
			_reg.GetComponent<Sprite>(_id).SetLayer(layer);
	}
	
	void SetTag(const std::string& tag) { _tag = tag; }
	const std::string& GetTag() const { return _tag; }

	void LoadScene(const std::string& name) { _changeScene.Dispatch(name); }
	std::shared_ptr<GameObject> Instantiate()
	{
		std::shared_ptr<GameObject> result;
		_instantiatePromise.Dispatch(result);
		return result;
	};
	void Destroy(GameObject* gameObject) 
	{
		_destroyObject.Dispatch(gameObject);
	}

	Camera* GetCamera()
	{ 
		return _camera;
	}

private:
	bool _active{ true };

	ecs::EntityId _id;
	ecs::Registry& _reg;
	Physics::PhysicsWorld& _physicsWorld;
	Events::EventDispatcher<const std::string&>& _changeScene;
	Events::EventDispatcher<std::shared_ptr<GameObject>&> _instantiatePromise{};
	Events::EventDispatcher<GameObject*> _destroyObject{};
	Camera* _camera = nullptr;
	std::string _tag;

	template<typename T>
	T* _AddComponent(T component)
	{
		return &_reg.AddComponent<T>(_id, std::move(component)); 
	}
};
