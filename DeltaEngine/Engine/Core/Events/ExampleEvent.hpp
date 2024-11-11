#pragma once

#include "Event.hpp"

namespace Events
{
	template<typename T>
	class ExampleEvent : public Events::Event
	{
	public:
		ExampleEvent(T value)
			: _value(value)
		{

		}

		T ExampleEvent()
		{
			return _value;
		}

	private:
		T _value;
	};
}