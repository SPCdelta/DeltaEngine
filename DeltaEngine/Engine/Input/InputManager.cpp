#include "InputManager.hpp"

// Singleton instance
InputManager InputManager::instance;

// Constructor
InputManager::InputManager() {}

// Get instance
InputManager& InputManager::GetInstance()
{
	return instance;
}

// Destructor
InputManager::~InputManager() {}

// Activate/deactivate input categories
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
							 Events::EventCallback<KeyListener&> keyEvent,
							 std::string category)
{
	keyInputState[PressedDown].add(InputsEnum::toStr(keyDown), category,
								   keyEvent);
}

void InputManager::keyPressed(Key keyDown,
							  Events::EventCallback<KeyListener&> keyEvent,
							  std::string category)
{
	keyInputState[Pressed].add(InputsEnum::toStr(keyDown), category, keyEvent);
}

void InputManager::onKeyUp(Key keyUp,
						   Events::EventCallback<KeyListener&> keyEvent,
						   std::string category)
{
	keyInputState[Release].add(InputsEnum::toStr(keyUp), category, keyEvent);
}

void InputManager::onKeyDown(std::set<Key> keysDown,
							 Events::EventCallback<KeyListener&> keyEvent)
{
	std::string allKeysDown;
	for (const auto& key : keysDown)
		allKeysDown += InputsEnum::toStr(key);
	keyInputState[PressedDown].add(allKeysDown, "game-input", keyEvent);
}

void InputManager::keyPressed(std::set<Key> keysDown,
							  Events::EventCallback<KeyListener&> keyEvent)
{
	std::string allKeysDown;
	for (const auto& key : keysDown)
		allKeysDown += InputsEnum::toStr(key);
	keyInputState[Pressed].add(allKeysDown, "game-input", keyEvent);
}

// Mouse events
void InputManager::onMouseButtonDown(
	int button, Events::EventCallback<MouseListener&> buttonEvent)
{
	if (buttonDownInputMapping.find(button) == buttonDownInputMapping.end())
		buttonDownInputMapping[button] =
			Events::EventDispatcher<MouseListener&>();

	buttonDownInputMapping[button].Register(buttonEvent);
}

void InputManager::onMouseButtonUp(
	int button, Events::EventCallback<MouseListener&> buttonEvent)
{
	if (buttonUpInputMapping.find(button) == buttonUpInputMapping.end())
		buttonUpInputMapping[button] =
			Events::EventDispatcher<MouseListener&>();

	buttonUpInputMapping[button].Register(buttonEvent);
}

void InputManager::onMouseMove(Events::EventCallback<MouseListener&> mouseEvent)
{
	mouseMovement.Register(mouseEvent);
}

void InputManager::onMouseWheel(
	Events::EventCallback<WheelListener&> wheelEvent)
{
	mouseWheelMovement.Register(wheelEvent);
}

// Execute binding inputs
void InputManager::executeBindingInputsForState(InputState state)
{
	std::vector<std::string> keyResults;
	std::unordered_set<std::string> processedKeys;

	std::vector<Key> inputKeys(pressedInputs.begin(), pressedInputs.end());

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

	auto allInputs = KeyListener(pressedInputs, true, -1, -1);
	// TODO: Include other inputs

	for (const auto& keyInput : keyResults)
	{
		keyInputState[state].dispatchActive(keyInput, allInputs);
	}
}

// Key updates
void InputManager::updateKeyDown(Key input)
{
	if (pressedInputs.find(input) == pressedInputs.end())
	{
		pressedInputs.insert(input);
		executeBindingInputsForState(PressedDown);
	}
}

void InputManager::updateKeyUp(Key input)
{
	pressedInputs.erase(input);
	auto allInputs = KeyListener(pressedInputs, true, -1, -1);
	// TODO: Include other inputs

	keyInputState[Release].dispatchActive(InputsEnum::toStr(input), allInputs);
}

// Mouse updates
void InputManager::updateMouseButtonDown(MouseListener& button)
{
	buttonDownInputMapping[button.button].Dispatch(button);
}

void InputManager::updateMouseButtonUp(MouseListener& button)
{
	buttonUpInputMapping[button.button].Dispatch(button);
}

void InputManager::updateMouseMovement(MouseListener& mouse)
{
	mouseMovement.Dispatch(mouse);
}

void InputManager::updateMouseWheel(WheelListener& mouse)
{
	mouseWheelMovement.Dispatch(mouse);
}

// Execute input events
void InputManager::executeInputEvents()
{
	executeBindingInputsForState(Pressed);
}
