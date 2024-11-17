#pragma once
#include <iostream>
#include <map>
#include "../Core/Events/EventDispatcher.hpp"
#include "KeyListener.hpp"


enum InputState
{
	PressedDown,
	Pressed,
	Release
};

class InputMapEventDispatchers
{
public:
	Events::EventDispatcher<KeyListener&>& operator[](std::string key) {
		return inputBindings[key];
	}

	bool find(std::string key) { 
		return inputBindings.find(key) != inputBindings.end();
	}

private:

	std::map<std::string, Events::EventDispatcher<KeyListener&>> inputBindings;
};

//InputEventDispatchers::InputEventDispatchers() {}
//
//InputEventDispatchers::~InputEventDispatchers() {}


//struct InputEventDispatcher
//{
//	std::string bindedInput;
//	Events::EventDispatcher<KeyListener&> inputEvent;
//
//	InputEventDispatcher(std::string input,
//						 Events::EventDispatcher<KeyListener&> inputEvent)
//		: bindedInput(input), inputEvent(inputEvent)
//	{
//	}
//};