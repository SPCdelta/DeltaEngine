#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>
#include "../Core/Events/EventDispatcher.hpp"
#include "../Core/Math/Point.hpp"
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
	static InputLocation keyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, std::string category = defaultCategory);
	static InputLocation onKeyReleased(Key keyUp, Events::EventCallback<Input&> keyEvent, std::string category = defaultCategory);

	//static void onKeyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent); TODO dit werkt op dit moment niet vanwege executeInputsPressedDown
	static InputLocation keyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent, std::string category = defaultCategory);

	static InputLocation onMouseButtonDown(MouseButton button, Events::EventCallback<Input&> buttonEvent, std::string category = defaultCategory);
	static InputLocation onMouseButtonUp(MouseButton button, Events::EventCallback<Input&> buttonEvent, std::string category = defaultCategory);
	static InputLocation onMouseMove(Events::EventCallback<Input&> mouseEvent, std::string category = defaultCategory);
	static InputLocation onMouseWheel(Events::EventCallback<Input&> wheelEvent, std::string category = defaultCategory);


	static Math::Point GetMousePosition()
	{
		return Math::Point{instance_.allInputs.mouseX, instance_.allInputs.mouseY};
	}


	void updateKeyDown(Key input);
	void updateKeyUp(Key input);

	void updateMouseButtonDown(MouseButton button);
	void updateMouseButtonUp(MouseButton button);
	void updateMouseMovement(int x, int y);
	void updateMouseWheel(int wheelVertically);

	void executeInputEvents();

	void remove(InputLocation inputLoc);

	static constexpr const char* defaultCategory = "Default";

   private:
	static InputManager instance_;


	Input allInputs;

	std::map<InputState, InputEventDispatchers> inputState;

	std::map<std::string, Events::EventDispatcher<Input&>> mouseMovement;
	std::map < std::string, Events::EventDispatcher<Input&>> mouseWheelMovement;
};
