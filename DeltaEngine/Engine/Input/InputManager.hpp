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
#include "DeltaInputs.hpp"
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

	void onKeyDown(Key keyDown, Events::EventCallback<Input&> keyEvent, std::string category = defaultCategory);
	void keyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, std::string category = defaultCategory);
	void onKeyUp(Key keyUp, Events::EventCallback<Input&> keyEvent, std::string category = defaultCategory);

	void onKeyDown(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent);
	void keyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent);

	void onMouseButtonDown(Button button, Events::EventCallback<Input&> buttonEvent, std::string category = defaultCategory);
	void onMouseButtonUp(Button button, Events::EventCallback<Input&> buttonEvent, std::string category = defaultCategory);
	void onMouseMove(Events::EventCallback<Input&> mouseEvent);
	void onMouseWheel(Events::EventCallback<Input&> wheelEvent);


	void updateKeyDown(Key input);
	void updateKeyUp(Key input);

	void updateMouseButtonDown(Button button);
	void updateMouseButtonUp(Button button);
	void updateMouseMovement(int x, int y);
	void updateMouseWheel(int wheelVertically);

	void executeInputEvents();

   private:
	static InputManager instance;
	static constexpr const char* defaultCategory = "Default";

	static Input allInputs;

	std::map<InputState, InputEventDispatchers> inputState;


	Events::EventDispatcher<Input&> mouseMovement{};
	Events::EventDispatcher<Input&> mouseWheelMovement{};
};
