#pragma once

#include <memory>
#include <entt/entt.hpp>
#include <iostream>

class BehaviourScript;

namespace ecs
{
	using EntityId = entt::entity;

	// Temporary until solution for below
	template <typename... Components>
	using View = entt::basic_view<entt::get_t<entt::storage_type_t<Components>...>, entt::exclude_t<>>;

	template<typename... Components>
	class System
	{
	public:
		System(ecs::View<Components...> view)
			: _view(view)
		{

		}

	protected:
		ecs::View<Components...> _view;
	};

	//class ecs::Registry;

	//template<typename... Components>
	//class System
	//{
	//public:
	//	System(const ecs::Registry* reg)
	//		: _view(reg)
	//	{

	//	}

	//protected:
	//	ecs::View<Components...> _view;
	//};

	class Registry
	{
	public:
		//friend class ecs::View;
		template<typename... Components>
		ecs::EntityId CreateEntity()
		{
			return _registry.create();
		}

		void DestroyEntity(ecs::EntityId entityId)
		{
			_registry.destroy(entityId);
		}

		template<typename T, typename... Components, typename... Args>
		std::shared_ptr<T> CreateSystem(Args&&... args)
		{
			std::shared_ptr<T> system{ std::make_shared<T>(_registry.view<Components...>(), std::forward<Args>(args)...) };
			return system;
		}


		template<typename Component>
		Component& AddComponent(ecs::EntityId entityId, Component component)
		{
			return _registry.emplace<Component>(entityId, component);
		}

		template<typename Component, typename... Args>
		Component& EmplaceComponent(ecs::EntityId entityId, Args&&... args)
		{
			return _registry.emplace<Component>(entityId, std::forward<Args>(args)...);
		}

		template<typename TBase, typename TInherit, typename... Args>
		TInherit* AddInheritanceComponent(ecs::EntityId entityId, Args&&... args) 
		{
			static_assert(std::is_base_of<TBase, TInherit>::value, "TInherit must inherit from TBase!");
			return static_cast<TInherit*>(_registry.emplace<std::unique_ptr<TBase>>(entityId, std::make_unique<TInherit>(std::forward<Args>(args)...)).get());
		}

		template<typename Component>
		void RemoveComponent(ecs::EntityId entityId)
		{
			_registry.remove<Component>(entityId);
		}

		template<typename Component>
		bool HasComponent(ecs::EntityId entityId)
		{
			return _registry.all_of<Component>(entityId);
		}

		template<typename Component>
		Component& GetComponent(ecs::EntityId entityId)
		{
			return _registry.get<Component>(entityId);
		}

		bool Valid(ecs::EntityId entityId)
		{
			return _registry.valid(entityId);
		}

		entt::registry _registry;
	private:
	};
}


