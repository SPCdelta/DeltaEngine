#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>
#include "../Core/Events/EventDispatcher.hpp"
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

	static InputLocation onKeyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, std::string category = defaultCategory);
	static InputLocation keyPressed(Key keyDown,
									Events::EventCallback<Input&> keyEvent,
									std::string category = defaultCategory);
	static InputLocation onKeyRealesed(Key keyUp,
									   Events::EventCallback<Input&> keyEvent,
							  std::string category = defaultCategory);

	//static void onKeyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent); TODO dit werkt op dit moment niet vanwege executeInputsPressedDown
	static InputLocation keyPressed(std::set<Key> keysDown,
									Events::EventCallback<Input&> keyEvent,
									std::string category = defaultCategory);

	static InputLocation onMouseButtonDown(
		Button button,
								  Events::EventCallback<Input&> buttonEvent,
								  std::string category = defaultCategory);
	static InputLocation onMouseButtonUp(
		Button button,
								Events::EventCallback<Input&> buttonEvent,
								std::string category = defaultCategory);
	static InputLocation onMouseMove(Events::EventCallback<Input&> mouseEvent);
	static InputLocation onMouseWheel(Events::EventCallback<Input&> wheelEvent);


	void updateKeyDown(Key input);
	void updateKeyUp(Key input);

	void updateMouseButtonDown(Button button);
	void updateMouseButtonUp(Button button);
	void updateMouseMovement(int x, int y);
	void updateMouseWheel(int wheelVertically);

	void executeInputEvents();

	void remove(InputLocation inputLoc);

	static constexpr const char* defaultCategory = "Default";

   private:
	static InputManager instance_;


	Input allInputs;

	std::map<InputState, InputEventDispatchers> inputState;

	Events::EventDispatcher<Input&> mouseMovement;
	Events::EventDispatcher<Input&> mouseWheelMovement;
};
