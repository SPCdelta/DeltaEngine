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
#include "UI/Scrollable.hpp"
#include "UI/Brush/SnapToGridBrush.hpp"
#include "UI/Brush/BrushSprite.hpp"

#include "Core/Events/EventDispatcher.hpp"

class Scene;
class BehaviourScript;
class ParticleEmitter;

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
			T* component = _reg.AddInheritanceComponent<BehaviourScript, T>(_id, std::forward<Args>(args)...);
			component->transform = transform;
			component->camera = _camera;
			component->OnStart();
			return component;
		}
		else if constexpr (std::is_base_of_v<Physics::Collider, T>)
		{
			T* component = _reg.AddInheritanceComponent<Physics::Collider, T>(_id, _physicsWorld, *transform, std::forward<Args>(args)...);
			return component;
		}
		else if constexpr (std::is_same_v<T, Physics::Rigidbody>)
		{
			if (!_reg.HasComponent<std::unique_ptr<Physics::Collider>>(_id))
			{
				throw std::exception("Rigidbody must have a Collider!");
			}

			Physics::Collider* collider = _reg.GetComponent<std::unique_ptr<Physics::Collider>>(_id).get();
			return static_cast<Physics::Rigidbody*>(&_reg.EmplaceComponent<Physics::Rigidbody>(_id, *collider));
		}
		else if constexpr (std::is_same_v<T, Ui::Button>)
		{
			T* component = static_cast<T*>(&_reg.EmplaceComponent<Ui::Button>(_id, transform));
			return component;
		}
		else if constexpr (std::is_same_v<T, Ui::Scrollable>)
		{
			T* component = static_cast<T*>(&_reg.EmplaceComponent<Ui::Scrollable>(_id, transform, std::forward<Args>(args)...));
			return component;
		}
		else if constexpr (std::is_same_v<T, SnapToGridBrush>)
		{
			Sprite* sprite = AddComponent<Sprite>("default_texture");
			T* component = static_cast<T*>(&_reg.EmplaceComponent<SnapToGridBrush>(_id, *transform, sprite, _camera, std::forward<Args>(args)...));
			
			return component;
		}
		else if constexpr (std::is_same_v<T, BrushSprite>)
		{
			T* component = static_cast<T*>(&_reg.EmplaceComponent<BrushSprite>(_id, *transform, std::forward<Args>(args)...));

			return component;
		}
		else if constexpr (std::is_same_v<T, ParticleEmitter>)
		{
			T* component = static_cast<T*>(&_reg.EmplaceComponent<ParticleEmitter>(_id, this, std::forward<Args>(args)...));
			return component;
		}
		else
		{
			return static_cast<T*>(&_reg.EmplaceComponent<T>(_id, std::forward<Args>(args)...));
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
			return *static_cast<T*>(_reg.GetComponent<std::unique_ptr<BehaviourScript>>(_id).get());
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

	ecs::EntityId GetId() const;

	GameObject(Scene* scene, ecs::EntityId id, ecs::Registry& reg, Physics::PhysicsWorld& physicsWorld, Camera* camera, Transform& transform_);
	~GameObject();

	friend class Scene;

	Scene* _scene;
	Transform& transformRef;
	Transform* transform = nullptr;

	bool IsActive() const;
	void SetActive(bool active);

	Layer GetLayer() const;
	void SetLayer(Layer layer);
	
	void SetTag(const std::string& tag);
	const std::string& GetTag() const;

	void LoadScene(const std::string& name);

	std::shared_ptr<GameObject> Instantiate();
	std::shared_ptr<GameObject> Instantiate(Transform transform);

	void Destroy();

	Camera* GetCamera();

	void GetWalkableTiles(std::vector<Transform*>& tiles, std::vector<Transform*>& walls);

private:
	bool _active{ true };

	ecs::EntityId _id;
	ecs::Registry& _reg;
	Physics::PhysicsWorld& _physicsWorld;

	Camera* _camera = nullptr;

	std::string _tag;

	template<typename T>
	T* _AddComponent(T component)
	{
		return &_reg.AddComponent<T>(_id, std::move(component)); 
	}
};
