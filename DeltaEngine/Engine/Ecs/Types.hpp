#pragma once

#include <entt/entt.hpp>

namespace ecs
{
	using EntityId = entt::entity;

	template <typename... Components>
	using View = entt::basic_view<entt::get_t<entt::storage_type_t<Components>...>, entt::exclude_t<>>;
}