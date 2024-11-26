#pragma once

#include "../Core/Events/EventDispatcher.hpp"

struct MyEvent
{

};

class Button
{
public:
	Events::EventDispatcher<MyEvent> onClick{};

	void Test()
	{ 
		MyEvent e{};
		onClick.Dispatch(e);

		// Dit moet dan in BehaviourScript implementatie om de klik af te vangen
		onClick.Register(
			[this](MyEvent& e) 
			{ 
				
			}
		);
	}
};