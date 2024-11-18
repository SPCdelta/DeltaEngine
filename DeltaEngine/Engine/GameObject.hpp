#pragma once

#include <vector>
#include <type_traits>

#include "Transform.hpp"
#include "BehaviourScript.hpp"

#include "Ecs/Registry.hpp"

#include "Rendering/Sprite.hpp"

#include "Physics/Collider.hpp"
#include "Physics/Rigidbody.hpp"

class GameObject
{
public:
	template <typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		// Useful code but not yet fully able to be used
		// https://github.com/SPCdelta/POC-Physics/blob/main/SDL2Box2DTest/src/Engine/GameObject.hpp
		//
		//if constexpr (std::is_same_v<T, BoxCollider2D>)
		//{
		//	return static_cast<T*>(AddComponent<BoxCollider2D>(BoxCollider2D(*transform)));
		//}
		//else if constexpr (std::is_same_v<T, Rigidbody>)
		//{
		//	// A Rigidbody must also have a Collider
		//	if (!_reg.HasComponent<BoxCollider2D>(_id))
		//	{
		//		return nullptr;
		//	}
		//
		//	return static_cast<T*>(AddComponent<Rigidbody>(Rigidbody(RigidbodyType::DYNAMIC_BODY, GetComponent<BoxCollider2D>())));
		//}
		//else if constexpr (std::is_base_of_v<BehaviourScript, T>)
		//{
		//	T* t{ static_cast<T*>(_reg.AddComponent<BehaviourScript*>(_id, new T())) };
		//	static_cast<BehaviourScript*>(t)->SetGameObject(this);
		//	return t;
		//	//return static_cast<T*>(AddComponent<BehaviourScript*>(new T())); // errors due to pointer types on addcomponent
		//}
		//else
		//{
		//	return static_cast<T*>(AddComponent<T>({}));
		//}

		if constexpr (std::is_base_of_v<BehaviourScript, T>)
		{
			T* component = static_cast<T*>(_reg.AddComponent<BehaviourScript*>(_id, new T()));
			component->SetGameObject(this);
			return component;
		}
		//else if constexpr (std::is_base_of_v<Physics::Collider, T>)
		//{
		//	T* component = static_cast<T*>(_reg.AddComponent<Physics::Collider*>(_id, new T()));
		//	return component;
		//}
		//else if constexpr (std::is_same_v<T, Physics::Rigidbody>)
		//{
		//	if (_reg.HasComponent<Physics::Collider*>(_id))
		//	{
		//		throw std::exception("Rigidbody must have a Collider!");
		//	}

		//	return static_cast<T*>(_AddComponent<Physics::Rigidbody>(Physics::Rigidbody(*_reg.GetComponent<Physics::Collider*>(_id))));
		//}
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

	GameObject(ecs::Registry& reg, Transform newTransform = {{0.0f, 0.0f}, 0.0f, {1.0f, 1.0f}});
	~GameObject();

	Transform* transform = nullptr;

	bool IsActive() const { return _active; }
	bool SetActive(bool active) { _active = active; }

private:
	bool _active{ true };

	ecs::EntityId _id;
	ecs::Registry& _reg;

	template<typename T>
	T* _AddComponent(T component)
	{
		return &_reg.AddComponent<T>(_id, component);
	}
};

