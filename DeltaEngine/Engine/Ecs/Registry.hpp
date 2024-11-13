#pragma once

#include <memory>
#include <entt/entt.hpp>

#include "View.hpp"

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
		template<typename... Components>
		//friend class ecs::View;

		ecs::EntityId CreateEntity()
		{
			return _registry.create();
		}

		void DestroyEntity(ecs::EntityId entityId)
		{
			_registry.destroy(entityId);
		}

		template<typename T, typename... Components>
		std::shared_ptr<T> CreateSystem()
		{
			std::shared_ptr<T> system{ std::make_shared<T>(_registry.view<Components...>()) };
			return system;
			//std::shared_ptr<T> system{ std::make_shared<T>(this) };
			//return system;
		}

		template<typename Component>
		Component& AddComponent(ecs::EntityId entityId, Component component)
		{
			return _registry.emplace<Component>(entityId, component);
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

	private:
		entt::registry _registry;
	};
}

