#pragma once

#include <vector>

#include "Event.hpp"

namespace Events
{
	template<typename T>
	class EventDispatcher
	{
	public:
		void Register(Events::EventCallback<T> callback)
		{
			m_Callbacks.push_back(callback);
		}

		void Unregister(Events::EventCallback<T> callback)
		{
			auto it = std::find_if(m_Callbacks.begin(), m_Callbacks.end(),
			[&callback](const Events::EventCallback<T>& cb) 
			{
				return callback.target<void(T&)>() == cb.target<void(T&)>();
			});

			if (it != m_Callbacks.end()) 
			{
				m_Callbacks.erase(it);
			}
		}

		void Dispatch(T& event)
		{
			for (size_t i = 0; i < m_Callbacks.size(); ++i)
			{
				m_Callbacks[i](event);
			}
		}

	private:
		std::vector<Events::EventCallback<T>> m_Callbacks{};
	};
}