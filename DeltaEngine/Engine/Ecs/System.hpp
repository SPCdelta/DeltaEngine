#pragma once

//#include "Types.hpp"
#include "Registry.hpp"

namespace ecs
{
	//class Registry;

	template<typename... Components>
	class System
	{
	public:
		System(ecs::Registry& reg)
			: _reg(reg), _view{ reg.GetView<Components...>() }
		{

		}

		void RefreshView()
		{
			_view = _reg.GetView<Components...>();
		}

		ecs::View<Components...> GetView()
		{
			return _reg.GetView<Components...>();
		}

	protected:
		ecs::Registry& _reg;
		ecs::View<Components...> _view;
	};
}