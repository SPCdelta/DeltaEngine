#pragma once

#include <functional>

namespace Events
{
	template<typename T>
	using EventCallback = std::function<void(T&)>; //Only Lambda

	class Event
	{
	public:
		virtual ~Event() = default;
	};
}