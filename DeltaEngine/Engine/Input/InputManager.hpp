#pragma once
#include "../Core/Events/EventDispatcher.hpp"
#include <map>
#include "IKeyListener.hpp"
#include "IMouseListener.hpp"

class InputManager
{
public:
	//Singleton
	InputManager();

	static InputManager& GetInstance() { return instance; }
	~InputManager();
	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager& operator=(InputManager&&) = delete;
	//end Singleton

	/*Events::EventDispatcher<IKeyListener&> onKeyUp{};
	Events::EventDispatcher<IMouseListener&> onMouseMove{};
	Events::EventDispatcher<IMouseListener&> onMouseButton{};
	Events::EventDispatcher<IMouseListener&> onScroll{};*/

	//TODO string mabye to enum??
	void onKeyDown(const std::string keyDown, Events::EventCallback<IKeyListener&> keyEvent)
	{
		if (keyDownInputMapping.find(keyDown) == keyDownInputMapping.end())
			keyDownInputMapping[keyDown] = Events::EventDispatcher<IKeyListener&>();

		keyDownInputMapping[keyDown].Register(keyEvent);
	}

	//Expects a static funciton or a lambda
	void setKeyDown(IKeyListener& key)
	{ 
		keyDownInputMapping[key.key].Dispatch(key);
	}

private:
	static InputManager instance;

	std::map<std::string /*miss key enum van keys*/,
			 Events::EventDispatcher<IKeyListener&>>
		keyDownInputMapping;
};
