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

class InputListener;

class InputManager
{
   public:
	static InputManager& GetInstance();
	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager& operator=(InputManager&&) = delete;



	static void deactivateCategory(const std::string& category);
	static void activateCategory(const std::string& category);

	static InputListener* onKeyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, const std::string & = defaultCategory);
	static InputListener* keyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, const std::string & = defaultCategory);
	static InputListener* onKeyReleased(Key keyUp, Events::EventCallback<Input&> keyEvent, const std::string & = defaultCategory);

	static InputListener* keyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent, const std::string& category = defaultCategory);

	static InputListener* onMouseButtonDown(MouseButton button, Events::EventCallback<Input&> buttonEvent, const std::string& category = defaultCategory);
	static InputListener* onMouseButtonUp(MouseButton button, Events::EventCallback<Input&> buttonEvent, const std::string& category = defaultCategory);
	static InputListener* onMouseMove(Events::EventCallback<Input&> mouseEvent, const std::string& category = defaultCategory);
	static InputListener* onMouseWheel(Events::EventCallback<Input&> wheelEvent, const std::string& = defaultCategory);


	static Math::Point GetMousePosition();


	void updateKeyDown(Key input);
	void updateKeyUp(Key input);

	void updateMouseButtonDown(MouseButton button);
	void updateMouseButtonUp(MouseButton button);
	void updateMouseMovement(Math::Point pos);
	void updateMouseWheel(int wheelVertically);

	void executeInputEvents();

	void Remove(InputListener* input);

	static constexpr const char* defaultCategory = "Default";

   private:
	InputManager();
	static InputManager instance_;

	Input allInputs;

	std::map<InputType, InputEventDispatchers> inputTypes;
};

