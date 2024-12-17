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
	// Singleton
	static InputManager& GetInstance();
	~InputManager();
	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager& operator=(InputManager&&) = delete;

	static void deactivateCategory(const std::string& category);
	static void activateCategory(const std::string& category);

	static std::unique_ptr<InputListener> onKeyPressed(Key keyDown, Events::EventCallback<Input&>& keyEvent, const std::string & = defaultCategory);
	static std::unique_ptr<InputListener> keyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, const std::string & = defaultCategory);
	static std::unique_ptr<InputListener> onKeyReleased(Key keyUp, Events::EventCallback<Input&> keyEvent, const std::string & = defaultCategory);

	//static void onKeyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent); TODO dit werkt op dit moment niet vanwege executeInputsPressedDown
	static std::unique_ptr<InputListener> keyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent, const std::string& category = defaultCategory);

	static std::unique_ptr<InputListener> onMouseButtonDown(MouseButton button, Events::EventCallback<Input&> buttonEvent, const std::string& category = defaultCategory);
	static std::unique_ptr<InputListener> onMouseButtonUp(MouseButton button, Events::EventCallback<Input&> buttonEvent, const std::string& category = defaultCategory);
	static std::unique_ptr<InputListener> onMouseMove(Events::EventCallback<Input&> mouseEvent, const std::string& category = defaultCategory);
	static std::unique_ptr<InputListener> onMouseWheel(Events::EventCallback<Input&> wheelEvent, const std::string& = defaultCategory);


	static Math::Point GetMousePosition();


	void updateKeyDown(Key input);
	void updateKeyUp(Key input);

	void updateMouseButtonDown(MouseButton button);
	void updateMouseButtonUp(MouseButton button);
	void updateMouseMovement(int x, int y);
	void updateMouseWheel(int wheelVertically);

	void executeInputEvents();

	void Remove(InputType type, const std::string& input, InputState state, const std::string& category, Events::EventCallback<Input&>& regesterd);

	static constexpr const char* defaultCategory = "Default";

   private:
	InputManager();
	static InputManager instance_;

	Input allInputs;

	std::map<InputType, InputEventDispatchers> inputState;

	std::map<std::string, Events::EventDispatcher<Input&>> mouseMovement;
	std::map<std::string, Events::EventDispatcher<Input&>> mouseWheelMovement;
};



class InputListener
{
public:
	InputListener(InputType type, const std::string& input, InputState state, const	std::string& category, Events::EventCallback<Input&>& regesterd)
		: _type{ type }, _input{ input }, _state{ state }, _category{ category }, _regesterd{ regesterd } {}
	~InputListener()
	{
		InputManager::GetInstance().Remove(_type, _input, _state, _category, _regesterd);
	}

private:
	InputType _type;
	std::string _input;
	InputState _state;
	std::string _category;
	Events::EventCallback<Input&>& _regesterd;
};
