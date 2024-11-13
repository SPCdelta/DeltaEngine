#pragma once

#include <vector>
#include <type_traits>

#include "Transform.hpp"
#include "Ecs/Registry.hpp"

class GameObject
{
public:
	template<typename T>
	T* AddComponent()
	{
		// Useful code but not yet fully able to be used
		// https://github.com/SPCdelta/POC-Physics/blob/main/SDL2Box2DTest/src/Engine/GameObject.hpp
		
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

		return static_cast<T*>(AddComponent<T>({}));
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

	GameObject(ecs::Registry& reg);

	bool IsActive() const { return _active; }
	bool SetActive(bool active) { _active = active; }

	// Due to how EnTT works, this cannot be a smart pointer
	// if this objects Transform is accessed without it existing,
	// it will would give the same error as it being a smart pointer
	Transform* transform = nullptr;

private:
	bool _active{ true };

	ecs::EntityId _id;
	ecs::Registry& _reg;

	template<typename T>
	T* AddComponent(T component)
	{
		return &_reg.AddComponent<T>(_id, component);
	}
};

