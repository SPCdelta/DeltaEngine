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

	static void deactivateCategory(std::string category);
	static void activateCategory(std::string category);

	static void onKeyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, std::string category = defaultCategory);
	static void keyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, std::string category = defaultCategory);
	static void onKeyRealesed(Key keyUp, Events::EventCallback<Input&> keyEvent,
							  std::string category = defaultCategory);

	static void onKeyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent);
	static void keyPressed(std::set<Key> keysDown,
						   Events::EventCallback<Input&> keyEvent);

	static void onMouseButtonDown(Button button,
								  Events::EventCallback<Input&> buttonEvent,
								  std::string category = defaultCategory);
	static void onMouseButtonUp(Button button,
								Events::EventCallback<Input&> buttonEvent,
								std::string category = defaultCategory);
	static void onMouseMove(Events::EventCallback<Input&> mouseEvent);
	static void onMouseWheel(Events::EventCallback<Input&> wheelEvent);


	void updateKeyDown(Key input);
	void updateKeyUp(Key input);

	void updateMouseButtonDown(Button button);
	void updateMouseButtonUp(Button button);
	void updateMouseMovement(int x, int y);
	void updateMouseWheel(int wheelVertically);

	void executeInputEvents();

   private:
	static InputManager instance_;

	static constexpr const char* defaultCategory = "Default";

	Input allInputs;

	std::map<InputState, InputEventDispatchers> inputState;

	Events::EventDispatcher<Input&> mouseMovement;
	Events::EventDispatcher<Input&> mouseWheelMovement;
};
