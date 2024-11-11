//#pragma once
//
//#include <entt/entt.hpp>
//#include "Registry.hpp"
//
//namespace ecs
//{
//	class ecs::Registry;
//
//	using EntityId = entt::entity;
//
//	// Cant intialize this without an ecs::Registry
//	template<typename... Components>
//	class View
//	{
//	public:
//		//View(entt::basic_view<entt::get_t<entt::storage_type_t<Components>...>, entt::exclude_t<>> view)
//		//	: _view{ view }
//		//{
//
//		//}
//
//		View(ecs::Registry reg)
//			: _view{ reg->view<Components...> }
//		{
//			
//		}
//
//		//auto begin() const
//		//{
//		//	return _view.begin();
//		//}
//
//		//auto end() const
//		//{
//		//	return _view.end();
//		//}
//
//		//template<typename Component>
//		//Component& get(ecs::EntityId entityId) const
//		//{
//		//	return _view.template get<Component>(entityId);
//		//}
//
//	private:
//		entt::basic_view<entt::get_t<entt::storage_type_t<Components>...>, entt::exclude_t<>> _view;
//	};
//}