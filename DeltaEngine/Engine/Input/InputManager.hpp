#pragma once
#include "../Core/Events/EventDispatcher.hpp"
#include "../Core/Utils/StableIndexList.hpp"
#include <map>
#include "KeyListener.hpp"
#include "MouseListener.hpp"
#include "WheelListener.h"

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
	void onKeyUp(const std::string keyUp, Events::EventCallback<KeyListener&> keyEvent)
	{
		if (keyUpInputMapping.find(keyUp) == keyUpInputMapping.end())
			keyUpInputMapping[keyUp] =
				Events::EventDispatcher<KeyListener&>();

		keyUpInputMapping[keyUp].Register(keyEvent);
	}

	void onMouseButtonDown(int button, Events::EventCallback<MouseListener&> buttonEvent)
	{
		if (buttonDownInputMapping.find(button) == buttonDownInputMapping.end())
			buttonDownInputMapping[button] =
				Events::EventDispatcher<MouseListener&>();

		buttonDownInputMapping[button].Register(buttonEvent);
	}
	void onMouseButtonUp(int button, Events::EventCallback<MouseListener&> buttonEvent)
	{
		if (buttonUpInputMapping.find(button) == buttonUpInputMapping.end())
			buttonUpInputMapping[button] =
				Events::EventDispatcher<MouseListener&>();

		buttonUpInputMapping[button].Register(buttonEvent);
	}
	void onMouseMove(Events::EventCallback<MouseListener&> mouseEvent)
	{
		mouseMovement.Register(mouseEvent);
	}
	void onMouseWheel(Events::EventCallback<WheelListener&> wheelEvent) {
		mouseWheelMovement.Register(wheelEvent);
	}


	void updateKeyDown(KeyListener& key)
	{
		keyDownInputMapping[key.key].Dispatch(key);
	}

	void updateKeyUp(KeyListener& key)
	{
		keyUpInputMapping[key.key].Dispatch(key);
	}

	void updateMouseButtonDown(MouseListener& button)
	{
		buttonDownInputMapping[button.button].Dispatch(button);
	}

	void updateMouseButtonUp(MouseListener& button) {
		buttonUpInputMapping[button.button].Dispatch(button);	
	}

	void updateMouseMovement(MouseListener& mouse)
	{
		mouseMovement.Dispatch(mouse);
	}
	
	void updateMouseWheel(WheelListener& mouse)
	{
		mouseWheelMovement.Dispatch(mouse);
	}

private:
	static InputManager instance;

	StableIndexList<KeyListener> updatingKeyEvents{};


	std::map<std::string, Events::EventDispatcher<KeyListener&>>
		keyDownInputMapping;
	std::map<std::string, Events::EventDispatcher<KeyListener&>>
		keyUpInputMapping;

	std::map<int, Events::EventDispatcher<MouseListener&>> buttonDownInputMapping;
	std::map<int, Events::EventDispatcher<MouseListener&>> buttonUpInputMapping;

	Events::EventDispatcher<MouseListener&> mouseMovement{};
	Events::EventDispatcher<WheelListener&> mouseWheelMovement{};
};
