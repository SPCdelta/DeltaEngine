#include "InputManager.hpp"

InputManager InputManager::instance;
Input InputManager::allInputs;

InputManager::InputManager() {}

InputManager& InputManager::GetInstance()
{
	return instance;
}

InputManager::~InputManager() {}

void InputManager::deactivateCategory(std::string category)
{
	for (auto& input : keyInputState)
	{
		input.second.deactivateCategory(category);
	}
}

void InputManager::activateCategory(std::string category)
{
	for (auto& input : keyInputState)
	{
		input.second.activateCategory(category);
	}
}

// Register key events
void InputManager::onKeyDown(Key keyDown,
							 Events::EventCallback<Input&> keyEvent,
							 std::string category)
{
	keyInputState[PressedDown].add(InputsEnum::toStr(keyDown), category,
								   keyEvent);
}

void InputManager::keyPressed(Key keyDown,
							  Events::EventCallback<Input&> keyEvent,
							  std::string category)
{
	keyInputState[Pressed].add(InputsEnum::toStr(keyDown), category, keyEvent);
}

void InputManager::onKeyUp(Key keyUp, Events::EventCallback<Input&> keyEvent,
						   std::string category)
{
	keyInputState[Release].add(InputsEnum::toStr(keyUp), category, keyEvent);
}

void InputManager::onKeyDown(std::set<Key> keysDown,
							 Events::EventCallback<Input&> keyEvent)
{
	std::string allKeysDown;
	for (const auto& key : keysDown)
		allKeysDown += InputsEnum::toStr(key);
	keyInputState[PressedDown].add(allKeysDown, "game-input", keyEvent);
}

void InputManager::keyPressed(std::set<Key> keysDown,
							  Events::EventCallback<Input&> keyEvent)
{
	std::string allKeysDown;
	for (const auto& key : keysDown)
		allKeysDown += InputsEnum::toStr(key);
	keyInputState[Pressed].add(allKeysDown, "game-input", keyEvent);
}

// Mouse events
void InputManager::onMouseButtonDown(Button button, Events::EventCallback<Input&> buttonEvent)
{
	if (buttonDownInputMapping.find(button) == buttonDownInputMapping.end())
		buttonDownInputMapping[button] = Events::EventDispatcher<Input&>();

	buttonDownInputMapping[button].Register(buttonEvent);
}

void InputManager::onMouseButtonUp(Button button, Events::EventCallback<Input&> buttonEvent)
{
	if (buttonUpInputMapping.find(button) == buttonUpInputMapping.end())
		buttonUpInputMapping[button] = Events::EventDispatcher<Input&>();

	buttonUpInputMapping[button].Register(buttonEvent);
}

void InputManager::onMouseMove(Events::EventCallback<Input&> mouseEvent)
{
	mouseMovement.Register(mouseEvent);
}

void InputManager::onMouseWheel(
	Events::EventCallback<Input&> wheelEvent)
{
	mouseWheelMovement.Register(wheelEvent);
}

// Execute binding inputs
void InputManager::executeBindingInputsForState(InputState state)
{
	std::vector<std::string> keyResults;
	std::unordered_set<std::string> processedKeys;

	std::vector<Key> inputKeys(allInputs.keys.begin(), allInputs.keys.end());

	int n = inputKeys.size();
	for (int i = 1; i < (1 << n); ++i)
	{
		std::string combinedKey;
		for (int j = 0; j < n; ++j)
		{
			if (i & (1 << j))
			{
				combinedKey += InputsEnum::toStr(inputKeys[j]);
			}
		}

		if (keyInputState[state].find(combinedKey) &&
			processedKeys.find(combinedKey) == processedKeys.end())
		{
			keyResults.push_back(combinedKey);
			processedKeys.insert(combinedKey);
		}
	}

	for (const auto& keyInput : keyResults)
	{
		keyInputState[state].dispatchActive(keyInput, allInputs);
	}
}

// Key updates
void InputManager::updateKeyDown(Key input)
{
	if (allInputs.keys.find(input) == allInputs.keys.end())
	{
		allInputs.keys.insert(input);
		executeBindingInputsForState(PressedDown);
	}
}

void InputManager::updateKeyUp(Key input)
{
	allInputs.keys.erase(input);

	keyInputState[Release].dispatchActive(InputsEnum::toStr(input), allInputs);
}

// Mouse updates
void InputManager::updateMouseButtonDown(Button button)
{
	allInputs.button.insert(button);
		
	buttonDownInputMapping[button].Dispatch(allInputs);
}

void InputManager::updateMouseButtonUp(Button button)
{
	allInputs.button.erase(button);

	buttonUpInputMapping[button].Dispatch(allInputs);
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
	executeBindingInputsForState(Pressed);
}
