#pragma once
#include "../Core/Events/EventDispatcher.hpp"
#include <map>
#include "KeyListener.hpp"
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

	//TODO string mabye to enum??
	void onKeyDown(const std::string keyDown, Events::EventCallback<KeyListener&> keyEvent)
	{
		if (keyDownInputMapping.find(keyDown) == keyDownInputMapping.end())
			keyDownInputMapping[keyDown] = Events::EventDispatcher<KeyListener&>();

		keyDownInputMapping[keyDown].Register(keyEvent);
	}
	void onKeyUp(const std::string keyUp,
				   Events::EventCallback<KeyListener&> keyEvent)
	{
		if (keyUpInputMapping.find(keyUp) == keyUpInputMapping.end())
			keyUpInputMapping[keyUp] =
				Events::EventDispatcher<KeyListener&>();

		keyUpInputMapping[keyUp].Register(keyEvent);
	}

	void updateKeyDown(KeyListener& key)
	{ 
		keyDownInputMapping[key.key].Dispatch(key);
	}

	void updateKeyUp(KeyListener& key)
	{
		keyUpInputMapping[key.key].Dispatch(key);
	}
	

private:
	static InputManager instance;

	std::map<std::string, Events::EventDispatcher<KeyListener&>>
		keyDownInputMapping;
	std::map<std::string, Events::EventDispatcher<KeyListener&>>
		keyUpInputMapping;
};
