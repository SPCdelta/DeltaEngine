#pragma once

#include <memory>

#include "Types.hpp"

class BehaviourScript;

namespace ecs
{
	template <typename... Components>
	class System;

	class Registry
	{
	public:
		template<typename... Components>
		ecs::EntityId CreateEntity()
		{
			return _registry.create();
		}

		void DestroyEntity(ecs::EntityId entityId);

		template<typename T, typename... Components, typename... Args>
		std::shared_ptr<T> CreateSystem(Args&&... args)
		{
			std::shared_ptr<T> system{ std::make_shared<T>(*this, std::forward<Args>(args)...) };
			return system;
		}

		template<typename... Components>
		ecs::View<Components...> GetView()
		{
			return _registry.view<Components...>();
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

		bool Valid(ecs::EntityId entityId);

		entt::registry _registry;
	};
}
