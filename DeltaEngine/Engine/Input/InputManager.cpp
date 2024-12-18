#include "InputManager.hpp"

InputManager InputManager::instance_;


InputManager::InputManager() {}

InputManager& InputManager::GetInstance()
{
	return instance_;
}

InputManager::~InputManager() {}

void InputManager::deactivateCategory(const std::string& category)
{
	for (auto& input : instance_.inputState)
	{
		input.second.DeactivateCategory(category);
	}
}

void InputManager::activateCategory(const std::string& category)
{
	for (auto& input : instance_.inputState)
	{
		input.second.ActivateCategory(category);
	}
}

InputListener* InputManager::onKeyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, const std::string& category)
{
	instance_.inputState[KEYBOARD].Add(PressedDown, InputsEnum::toStr(keyDown), category, keyEvent);
	return new InputListener{KEYBOARD, InputsEnum::toStr(keyDown), PressedDown, category, keyEvent};
}

InputListener* InputManager::keyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, const std::string& category)
{
	instance_.inputState[KEYBOARD].Add(Pressed, InputsEnum::toStr(keyDown), category, keyEvent);
	return new InputListener{KEYBOARD, InputsEnum::toStr(keyDown), Pressed, category, keyEvent};
}

InputListener* InputManager::onKeyReleased(Key keyUp, Events::EventCallback<Input&> keyEvent, const std::string& category)
{
	instance_.inputState[KEYBOARD].Add(Release, InputsEnum::toStr(keyUp), category, keyEvent);
	return new InputListener{KEYBOARD, InputsEnum::toStr(keyUp), Release, category, keyEvent};
}

InputListener* InputManager::keyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent, const std::string& category)
{
	std::string allKeysDown;
	for (const auto& key : keysDown)
		allKeysDown += InputsEnum::toStr(key);

	instance_.inputState[KEYBOARD].Add(Pressed, allKeysDown, category, keyEvent);
	return new InputListener{KEYBOARD, allKeysDown, Pressed, category, keyEvent};
}

// Mouse events
InputListener* InputManager::onMouseButtonDown(MouseButton button, Events::EventCallback<Input&> buttonEvent, const std::string& category)
{
	std::string strButton = std::to_string(InputsEnum::toInt(button));

	instance_.inputState[MOUSEBUTTON].Add(PressedDown, strButton, category, buttonEvent);
	return new InputListener{ MOUSEBUTTON, strButton, PressedDown, category, buttonEvent };
}

InputListener* InputManager::onMouseButtonUp(MouseButton button, Events::EventCallback<Input&> buttonEvent, const std::string& category)
{	
	std::string strButton = std::to_string(InputsEnum::toInt(button));

	instance_.inputState[MOUSEBUTTON].Add(Release, strButton, category, buttonEvent);
	return new InputListener{MOUSEBUTTON, strButton, Release, category, buttonEvent };
}

InputListener* InputManager::onMouseMove(Events::EventCallback<Input&> mouseEvent, const std::string& category)
{
	instance_.inputState[MOUSEMOVEMENT].Add(Unknown, "MouseMove", category, mouseEvent);
	return new InputListener{MOUSEMOVEMENT, "MouseMove", Unknown, category, mouseEvent};
}

InputListener* InputManager::onMouseWheel(Events::EventCallback<Input&> wheelEvent, const std::string& category)
{
	instance_.inputState[MOUSEWHEELMOVEMENT].Add(Unknown, "MouseWheel", category, wheelEvent);
	return new InputListener{MOUSEWHEELMOVEMENT, "MouseWheel", Unknown, category, wheelEvent};

}

Math::Point InputManager::GetMousePosition()
{
	return Math::Point{ instance_.allInputs.mouseX, instance_.allInputs.mouseY };
}

void InputManager::updateKeyDown(Key input)
{
	if (allInputs.keys.find(input) == allInputs.keys.end())
	{
		allInputs.keys.insert(input);

		std::vector<std::string> strKeys;
		for (auto& key : allInputs.keys)
			strKeys.push_back(InputsEnum::toStr(key));
		inputState[KEYBOARD].ExecuteInputsPressedDown(allInputs, strKeys, InputsEnum::toStr(input));

	}
}

void InputManager::updateKeyUp(Key input)
{
	allInputs.keys.erase(input);

	inputState[KEYBOARD].DispatchActive(Release, InputsEnum::toStr(input), allInputs);
}

// Mouse updates
void InputManager::updateMouseButtonDown(MouseButton button)
{
	if (allInputs.buttons.find(button) == allInputs.buttons.end())
	{
		allInputs.buttons.insert(button);

		std::vector<std::string> strButtons;
		for (auto& button : allInputs.buttons)
			strButtons.push_back(std::to_string(InputsEnum::toInt(button)));
		inputState[MOUSEBUTTON].ExecuteInputsPressedDown(allInputs, strButtons, std::to_string(InputsEnum::toInt(button)));
	}
}

void InputManager::updateMouseButtonUp(MouseButton input)
{
	allInputs.buttons.erase(input);

	inputState[MOUSEBUTTON].DispatchActive(Release, std::to_string(InputsEnum::toInt(input)), allInputs);
}

void InputManager::updateMouseMovement(int x, int y)
{
	allInputs.mouseX = x;
	allInputs.mouseY = y;

	inputState[MOUSEMOVEMENT].DispatchActive(Unknown, "MouseMove", allInputs);
}

void InputManager::updateMouseWheel(int wheelVertically)
{
	allInputs.wheelVertically = wheelVertically;
	inputState[MOUSEWHEELMOVEMENT].DispatchActive(Unknown, "MouseWheel", allInputs);
}

// Execute input events
void InputManager::executeInputEvents()
{
	if (allInputs.buttons.empty() && allInputs.keys.empty())
		return;

	std::vector<std::string> strKeys;
	for (auto& key : allInputs.keys)
		strKeys.push_back(InputsEnum::toStr(key));

	for (auto& [type, input] : inputState)
		input.ExecuteInputsPressed(allInputs, strKeys);
}


void InputManager::Remove(InputType type, const std::string& input, InputState state, const std::string& category, Events::EventCallback<Input&>& regesterd)
{
	inputState[type].Remove(state, input, category, regesterd);
}
