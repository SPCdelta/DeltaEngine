#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>
#include "../Core/Events/EventDispatcher.hpp"
#include "../Core/Utils/StableIndexList.hpp"
#include "InputEventDispatchers.hpp"
#include "InputsEnum.hpp"
#include "KeyListener.hpp"
#include "MouseListener.hpp"
#include "WheelListener.hpp"

class InputManager
{
   public:
	// Singleton
	InputManager();
	static InputManager& GetInstance();
	~InputManager();
	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager& operator=(InputManager&&) = delete;

	void deactivateCategory(std::string category);
	void activateCategory(std::string category);

	void onKeyDown(Key keyDown, Events::EventCallback<KeyListener&> keyEvent,
				   std::string category = defaultCategory);
	void keyPressed(Key keyDown, Events::EventCallback<KeyListener&> keyEvent,
					std::string category = defaultCategory);
	void onKeyUp(Key keyUp, Events::EventCallback<KeyListener&> keyEvent,
				 std::string category = defaultCategory);

	void onKeyDown(std::set<Key> keysDown,
				   Events::EventCallback<KeyListener&> keyEvent);
	void keyPressed(std::set<Key> keysDown,
					Events::EventCallback<KeyListener&> keyEvent);

	void onMouseButtonDown(int button,
						   Events::EventCallback<MouseListener&> buttonEvent);
	void onMouseButtonUp(int button,
						 Events::EventCallback<MouseListener&> buttonEvent);
	void onMouseMove(Events::EventCallback<MouseListener&> mouseEvent);
	void onMouseWheel(Events::EventCallback<WheelListener&> wheelEvent);

	void executeBindingInputsForState(InputState state);

	void updateKeyDown(Key input);
	void updateKeyUp(Key input);
	void updateMouseButtonDown(MouseListener& button);
	void updateMouseButtonUp(MouseListener& button);
	void updateMouseMovement(MouseListener& mouse);
	void updateMouseWheel(WheelListener& mouse);

	void executeInputEvents();

   private:
	static InputManager instance;
	static constexpr const char* defaultCategory = "Default";

	std::set<Key> pressedInputs;
	std::map<InputState, InputEventDispatchers> keyInputState;

	std::map<int, Events::EventDispatcher<MouseListener&>>
		buttonDownInputMapping;
	std::map<int, Events::EventDispatcher<MouseListener&>> buttonUpInputMapping;

	Events::EventDispatcher<MouseListener&> mouseMovement{};
	Events::EventDispatcher<WheelListener&> mouseWheelMovement{};
};
