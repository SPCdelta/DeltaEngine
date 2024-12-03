#include "InputManager.hpp"

InputManager InputManager::instance_;


InputManager::InputManager() {}

InputManager& InputManager::GetInstance()
{
	return instance_;
}

InputManager::~InputManager() {}

void InputManager::deactivateCategory(std::string category)
{
	for (auto& input : instance_.inputState)
	{
		input.second.deactivateCategory(category);
	}
}

void InputManager::activateCategory(std::string category)
{
	for (auto& input : instance_.inputState)
	{
		input.second.activateCategory(category);
	}
}

InputLocation InputManager::onKeyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, std::string category)
{
	instance_.inputState[PressedDown].add(
		InputsEnum::toStr(keyDown), category, keyEvent);

	InputLocation inputLoc(InputsEnum::toStr(keyDown), PressedDown, category,
						   keyEvent);
	return inputLoc;
}

InputLocation InputManager::keyPressed(Key keyDown, Events::EventCallback<Input&> keyEvent, std::string category)
{
	instance_.inputState[Pressed].add(InputsEnum::toStr(keyDown), category, keyEvent);

	InputLocation inputLoc(InputsEnum::toStr(keyDown), Pressed, category, keyEvent);
	return inputLoc;
}

InputLocation InputManager::onKeyReleased(Key keyUp, Events::EventCallback<Input&> keyEvent, std::string category)
{
	instance_.inputState[Release].add(InputsEnum::toStr(keyUp), category, keyEvent);
	InputLocation inputLoc(InputsEnum::toStr(keyUp), Release, category, keyEvent);
	return inputLoc;
}

//void InputManager::onKeyPressed(std::set<Key> keysDown,
//							 Events::EventCallback<Input&> keyEvent)
//{
//	std::string allKeysDown;
//	for (const auto& key : keysDown)
//		allKeysDown += InputsEnum::toStr(key);
//	InputLocation inputLoc = instance_.inputState[PressedDown].add(allKeysDown, "game-input", keyEvent);
//}

InputLocation InputManager::keyPressed(std::set<Key> keysDown, Events::EventCallback<Input&> keyEvent, std::string category)
{
	std::string allKeysDown;
	for (const auto& key : keysDown)
		allKeysDown += InputsEnum::toStr(key);

	instance_.inputState[Pressed].add(allKeysDown, category, keyEvent);
	
	InputLocation inputLoc(allKeysDown, Pressed, category, keyEvent);
	return inputLoc;
}

// Mouse events
InputLocation InputManager::onMouseButtonDown(MouseButton button, Events::EventCallback<Input&> buttonEvent, std::string category)
{
	std::string strButton = std::to_string(InputsEnum::toInt(button));

	instance_.inputState[PressedDown].add(strButton, category, buttonEvent);

	InputLocation inputLoc(strButton, PressedDown, category, buttonEvent);
	return inputLoc;
}

InputLocation InputManager::onMouseButtonUp(MouseButton button, Events::EventCallback<Input&> buttonEvent, std::string category)
{	
	std::string strButton = std::to_string(InputsEnum::toInt(button));

	instance_.inputState[Release].add(strButton, category, buttonEvent);
	InputLocation inputLoc(strButton, Release, category, buttonEvent);
	
	return inputLoc;
}

InputLocation InputManager::onMouseMove(Events::EventCallback<Input&> mouseEvent)
{
	instance_.mouseMovement.Register(mouseEvent);
	return {"mouse-move", Unknown, "", mouseEvent};

}

InputLocation InputManager::onMouseWheel(Events::EventCallback<Input&> wheelEvent)
{
	instance_.mouseWheelMovement.Register(wheelEvent);
	return {"mouse-wheel", Unknown, "", wheelEvent};
}

void InputManager::updateKeyDown(Key input)
{
	if (allInputs.keys.find(input) == allInputs.keys.end())
	{
		allInputs.keys.insert(input);

		std::vector<std::string> strKeys;
		for (auto& key : allInputs.keys)
			strKeys.push_back(InputsEnum::toStr(key));
		inputState[PressedDown].executeInputsPressedDown(
			allInputs, strKeys, InputsEnum::toStr(input));

	}
}

void InputManager::updateKeyUp(Key input)
{
	allInputs.keys.erase(input);

	inputState[Release].dispatchActive(InputsEnum::toStr(input), allInputs);
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
		inputState[PressedDown].executeInputsPressedDown(allInputs, strButtons, std::to_string(InputsEnum::toInt(button)));
	}
}

void InputManager::updateMouseButtonUp(MouseButton input)
{
	allInputs.buttons.erase(input);

	inputState[Release].dispatchActive(std::to_string(InputsEnum::toInt(input)), allInputs);
}

void InputManager::updateMouseMovement(int x, int y)
{
	allInputs.mouseX = x;
	allInputs.mouseY = y;

	mouseMovement.Dispatch(allInputs);
}

void InputManager::updateMouseWheel(int wheelVertically)
{
	allInputs.wheelVertically = wheelVertically;
	mouseWheelMovement.Dispatch(allInputs);
}

// Execute input events
void InputManager::executeInputEvents()
{
	if (allInputs.buttons.empty() && allInputs.keys.empty())
		return;

	std::vector<std::string> strKeys;
	for (auto& key : allInputs.keys)
		strKeys.push_back(InputsEnum::toStr(key));

	inputState[Pressed].executeInputsPressed(allInputs, strKeys);
}

void InputManager::remove(InputLocation inputLoc) {
	if (inputLoc.input == "mouse-wheel")
	{
		mouseWheelMovement.Unregister(inputLoc.regesterd);
	}
	else if (inputLoc.input == "mouse-move")
	{
		mouseMovement.Unregister(inputLoc.regesterd);
	}
	else
	{
		inputState[inputLoc.state].remove(inputLoc);
	}
}
