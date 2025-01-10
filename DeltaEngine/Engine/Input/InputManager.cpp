#include "InputManager.hpp"
#include "InputHandler.hpp"

InputManager InputManager::instance_;


InputManager::InputManager() {}

InputManager& InputManager::GetInstance()
{
	return instance_;
}

void InputManager::deactivateCategory(const std::string& category)
{
	for (auto& input : instance_.inputTypes)
	{
		input.second.DeactivateCategory(category);
	}
}

void InputManager::activateCategory(const std::string& category)
{
	for (auto& input : instance_.inputTypes)
	{
		input.second.ActivateCategory(category);
	}
}

InputListener* InputManager::onKeyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, const std::string& category)
{
	InputListener* inputListener = new InputListener{ KEYBOARD, InputsEnum::toStr(keyDown), InputState::PressedDown, category, keyEvent };

	instance_.inputTypes[KEYBOARD].Add(inputListener);
	return inputListener;
}

InputListener* InputManager::keyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, const std::string& category)
{
	InputListener* inputListener = new InputListener{ KEYBOARD, InputsEnum::toStr(keyDown), Pressed, category, keyEvent };
	instance_.inputTypes[KEYBOARD].Add(inputListener);
	return inputListener;
}

InputListener* InputManager::onKeyReleased(Key keyUp, Events::EventCallback<Input&> keyEvent, const std::string& category)
{
	InputListener* inputListener = new InputListener{ KEYBOARD, InputsEnum::toStr(keyUp), Release, category, keyEvent };
	instance_.inputTypes[KEYBOARD].Add(inputListener);
	return inputListener;
}

InputListener* InputManager::keyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent, const std::string& category)
{
	std::string allKeysDown;
	for (const auto& key : keysDown)
		allKeysDown += InputsEnum::toStr(key);
	InputListener* inputListener = new InputListener{ KEYBOARD, allKeysDown, Pressed, category, keyEvent };
	instance_.inputTypes[KEYBOARD].Add(inputListener);
	return inputListener;
}

InputListener* InputManager::onMouseButtonDown(MouseButton button, Events::EventCallback<Input&> buttonEvent, const std::string& category)
{
	std::string strButton = std::to_string(InputsEnum::toInt(button));
	InputListener* inputListener = new InputListener{ MOUSEBUTTON, strButton, PressedDown, category, buttonEvent };
	instance_.inputTypes[MOUSEBUTTON].Add(inputListener);
	return inputListener;
}

InputListener* InputManager::onMouseButtonUp(MouseButton button, Events::EventCallback<Input&> buttonEvent, const std::string& category)
{	
	std::string strButton = std::to_string(InputsEnum::toInt(button));
	InputListener* inputListener = new InputListener{ MOUSEBUTTON, strButton, Release, category, buttonEvent };
	instance_.inputTypes[MOUSEBUTTON].Add(inputListener);
	return inputListener;
}

InputListener* InputManager::onMouseMove(Events::EventCallback<Input&> mouseEvent, const std::string& category)
{
	InputListener* inputListener = new InputListener{ MOUSEMOVEMENT, "MouseMove", Unknown, category, mouseEvent };
	instance_.inputTypes[MOUSEMOVEMENT].Add(inputListener);
	return inputListener;
}

InputListener* InputManager::onMouseWheel(Events::EventCallback<Input&> wheelEvent, const std::string& category)
{
	InputListener* inputListener = new InputListener{ MOUSEWHEELMOVEMENT, "MouseWheel", Unknown, category, wheelEvent };
	instance_.inputTypes[MOUSEWHEELMOVEMENT].Add(inputListener);
	return inputListener;

}

Math::Point InputManager::GetMousePosition()
{
	return Math::Point{ instance_.allInputs.mouseX, instance_.allInputs.mouseY };
}

void InputManager::updateKeyDown(Key input)
{
	// JInput
	std::cout << "Meow!" << std::endl;

	if (allInputs.keys.find(input) == allInputs.keys.end())
	{
		allInputs.keys.insert(input);

		std::vector<std::string> strKeys;
		for (auto& key : allInputs.keys)
		{
			_inputRegistry.Execute(key, allInputs);
			strKeys.push_back(InputsEnum::toStr(key));
		}

		inputTypes[KEYBOARD].ExecuteInputsPressedDown(allInputs, strKeys, InputsEnum::toStr(input));
	}
}

void InputManager::updateKeyUp(Key input)
{
	allInputs.keys.erase(input);

	inputTypes[KEYBOARD].DispatchActive(Release, InputsEnum::toStr(input), allInputs);
}

void InputManager::updateMouseButtonDown(MouseButton button)
{
	if (allInputs.buttons.find(button) == allInputs.buttons.end())
	{
		allInputs.buttons.insert(button);

		std::vector<std::string> strButtons;
		for (auto& button : allInputs.buttons)
			strButtons.push_back(std::to_string(InputsEnum::toInt(button)));
		inputTypes[MOUSEBUTTON].ExecuteInputsPressedDown(allInputs, strButtons, std::to_string(InputsEnum::toInt(button)));
	}
}

void InputManager::updateMouseButtonUp(MouseButton input)
{
	allInputs.buttons.erase(input);

	inputTypes[MOUSEBUTTON].DispatchActive(Release, std::to_string(InputsEnum::toInt(input)), allInputs);
}

void InputManager::updateMouseMovement(Math::Point pos)
{
	allInputs.mouseX = pos.GetX();
	allInputs.mouseY = pos.GetY();

	inputTypes[MOUSEMOVEMENT].DispatchActive(Unknown, "MouseMove", allInputs);
}

void InputManager::updateMouseWheel(int wheelVertically)
{
	allInputs.wheelVertically = wheelVertically;
	inputTypes[MOUSEWHEELMOVEMENT].DispatchActive(Unknown, "MouseWheel", allInputs);
}

void InputManager::executeInputEvents()
{
	if (allInputs.buttons.empty() && allInputs.keys.empty())
		return;

	std::vector<std::string> strKeys;
	for (auto& key : allInputs.keys)
		strKeys.push_back(InputsEnum::toStr(key));

	for (auto& [type, input] : inputTypes)
		input.ExecuteInputsPressed(allInputs, strKeys);
}

void InputManager::Remove(InputListener* input)
{
	inputTypes[input->GetType()].Remove(input);
}
