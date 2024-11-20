#pragma once
#include "../Core/Events/EventDispatcher.hpp"
#include "../Core/Utils/StableIndexList.hpp"
#include "InputEventDispatchers.hpp"
#include "KeyListener.hpp"
#include "MouseListener.hpp"
#include "WheelListener.hpp"
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_set>
#include "InputsEnum.hpp"

class InputManager
{
public:
	//Singleton
	InputManager();

	static InputManager& GetInstance() { return instance; }
	~InputManager();
	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager& operator=(InputManager&&) = delete;
	//end Singleton
	
	void deactivateCategory(std::string category) {
		for (auto& input : keyInputState)
		{
			input.second.deactivateCategory(category);
		}
	}

	void activateCategory(std::string category)
	{
		for (auto& input : keyInputState)
		{
			input.second.activateCategory(category);
		}
	}

	void onKeyDown(Key keyDown, Events::EventCallback<KeyListener&> keyEvent,
				   std::string category = defaultCategory)
	{
		keyInputState[PressedDown].add(InputsEnum::toStr(keyDown), category, keyEvent);
	}

	void keyPressed(Key keyDown, Events::EventCallback<KeyListener&> keyEvent,
					std::string category = defaultCategory)
	{
		keyInputState[Pressed].add(InputsEnum::toStr(keyDown), category, keyEvent);
	}
	void onKeyUp(Key keyUp, Events::EventCallback<KeyListener&> keyEvent,
				 std::string category = defaultCategory)
	{
		keyInputState[Release].add(InputsEnum::toStr(keyUp), category, keyEvent);
	}

	void onKeyDown(std::set<Key> keysDown,
				   Events::EventCallback<KeyListener&> keyEvent)
	{
		std::string allkeysDown;
		for (const auto& key : keysDown)
			allkeysDown += InputsEnum::toStr(key);
		keyInputState[PressedDown].add(allkeysDown, "game-input", keyEvent);
	}

	void keyPressed(std::set<Key> keysDown,
					Events::EventCallback<KeyListener&> keyEvent)
	{
		std::string allkeysDown;
		for (const auto& key : keysDown)
			allkeysDown += InputsEnum::toStr(key);
		keyInputState[Pressed].add(allkeysDown, "game-input", keyEvent);
	}

	void onMouseButtonDown(int button, Events::EventCallback<MouseListener&> buttonEvent)
	{
		if (buttonDownInputMapping.find(button) == buttonDownInputMapping.end())
			buttonDownInputMapping[button] =
				Events::EventDispatcher<MouseListener&>();

		buttonDownInputMapping[button].Register(buttonEvent);
	}
	void onMouseButtonUp(int button, Events::EventCallback<MouseListener&> buttonEvent)
	{
		if (buttonUpInputMapping.find(button) == buttonUpInputMapping.end())
			buttonUpInputMapping[button] =
				Events::EventDispatcher<MouseListener&>();

		buttonUpInputMapping[button].Register(buttonEvent);
	}
	void onMouseMove(Events::EventCallback<MouseListener&> mouseEvent)
	{
		mouseMovement.Register(mouseEvent);
	}
	void onMouseWheel(Events::EventCallback<WheelListener&> wheelEvent) {
		mouseWheelMovement.Register(wheelEvent);
	}

	void executeBindingInputsForState(InputState state)
	{
		std::vector<std::string> keyResults;

		std::unordered_set<std::string> processedKeys;

		std::vector<Key> inputKeys;
		for (const auto& kv : pressedInputs)
		{
			inputKeys.emplace_back(kv);
		}

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

			// Check if the combined key exists in the map and if it has not been processed
			if (keyInputState[state].find(combinedKey) &&
				processedKeys.find(combinedKey) == processedKeys.end())
			{
				keyResults.push_back(combinedKey);
				processedKeys.insert(
					combinedKey);  // Mark this combined key as processed
			}
		}

		auto allInputs = KeyListener(pressedInputs, true, -1, -1);  
		//TODO ook de rest van de inputs er by zetten


		for (const auto& keyInput : keyResults)
		{
			keyInputState[state].dispatchActive(keyInput, allInputs);
		}
	}


	void updateKeyDown(Key input)
	{
		if (std::find(pressedInputs.begin(), pressedInputs.end(), input) == pressedInputs.end())
		{
			pressedInputs.insert(input);
			executeBindingInputsForState(PressedDown);
		}
	}

	void updateKeyUp(Key input)
	{
		pressedInputs.erase(input);
		auto allInputs = KeyListener(pressedInputs, true, -1, -1);
		//TODO ook de rest van de inputs er by zetten

		keyInputState[Release].dispatchActive(InputsEnum::toStr(input), allInputs);
	}

	void updateMouseButtonDown(MouseListener& button)
	{
		buttonDownInputMapping[button.button].Dispatch(button);
	}

	void updateMouseButtonUp(MouseListener& button) {
		buttonUpInputMapping[button.button].Dispatch(button);	
	}

	void updateMouseMovement(MouseListener& mouse)
	{
		mouseMovement.Dispatch(mouse);
	}
	
	void updateMouseWheel(WheelListener& mouse)
	{
		mouseWheelMovement.Dispatch(mouse);
	}

	void executeInputEvents() { 
		executeBindingInputsForState(Pressed);
	}

private:
	static InputManager instance;
	static constexpr const char* defaultCategory = "Default";


	std::set<Key> pressedInputs;


	std::map<InputState, InputEventDispatchers> keyInputState;



	//old

	std::map<int, Events::EventDispatcher<MouseListener&>> buttonDownInputMapping;
	std::map<int, Events::EventDispatcher<MouseListener&>> buttonUpInputMapping;

	Events::EventDispatcher<MouseListener&> mouseMovement{};
	Events::EventDispatcher<WheelListener&> mouseWheelMovement{};
};
