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

// Register key events
void InputManager::onKeyPressed(Key keyDown,
							 Events::EventCallback<Input&> keyEvent,
							 std::string category)
{

	instance_.inputState[PressedDown].add(InputsEnum::toStr(keyDown), category,
								   keyEvent);
}

void InputManager::keyPressed(Key keyDown,
							  Events::EventCallback<Input&> keyEvent,
							  std::string category)
{
	instance_.inputState[Pressed].add(InputsEnum::toStr(keyDown), category,
									  keyEvent);
}

void InputManager::onKeyRealesed(Key keyUp, Events::EventCallback<Input&> keyEvent,
						   std::string category)
{
	instance_.inputState[Release].add(InputsEnum::toStr(keyUp), category,
									  keyEvent);
}

//void InputManager::onKeyPressed(std::set<Key> keysDown,
//							 Events::EventCallback<Input&> keyEvent)
//{
//	std::string allKeysDown;
//	for (const auto& key : keysDown)
//		allKeysDown += InputsEnum::toStr(key);
//	instance_.inputState[PressedDown].add(allKeysDown, "game-input", keyEvent);
//}

void InputManager::keyPressed(std::set<Key> keysDown,
							  Events::EventCallback<Input&> keyEvent)
{
	std::string allKeysDown;
	for (const auto& key : keysDown)
		allKeysDown += InputsEnum::toStr(key);
	instance_.inputState[Pressed].add(allKeysDown, "game-input", keyEvent);
}

// Mouse events
void InputManager::onMouseButtonDown(Button button, Events::EventCallback<Input&> buttonEvent, std::string category)
{
	instance_.inputState[PressedDown].add(
		std::to_string(InputsEnum::toInt(button)), category, buttonEvent);
}

void InputManager::onMouseButtonUp(Button button, Events::EventCallback<Input&> buttonEvent, std::string category)
{
	instance_.inputState[Release].add(std::to_string(InputsEnum::toInt(button)),
									  category, buttonEvent);
}

void InputManager::onMouseMove(Events::EventCallback<Input&> mouseEvent)
{
	instance_.mouseMovement.Register(mouseEvent);
}

void InputManager::onMouseWheel(
	Events::EventCallback<Input&> wheelEvent)
{
	instance_.mouseWheelMovement.Register(wheelEvent);
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
void InputManager::updateMouseButtonDown(Button button)
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

void InputManager::updateMouseButtonUp(Button input)
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
