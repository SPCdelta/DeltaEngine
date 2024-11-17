#pragma once
#include "../Core/Events/EventDispatcher.hpp"
#include "../Core/Utils/StableIndexList.hpp"
#include "KeyListener.hpp"
#include "MouseListener.hpp"
#include "WheelListener.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <unordered_set>

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

	//TODO string mabye to enum??
	void onKeyDown(const std::string keyDown, Events::EventCallback<KeyListener&> keyEvent)
	{
		if (onPressedInputBindings.find(keyDown) == onPressedInputBindings.end())
			onPressedInputBindings[keyDown] = Events::EventDispatcher<KeyListener&>();

		onPressedInputBindings[keyDown].Register(keyEvent);
	}

	void keyPressed(const std::string keyDown, Events::EventCallback<KeyListener&> keyEvent)
	{
		if (pressedInputBindings.find(keyDown) == pressedInputBindings.end())
			pressedInputBindings[keyDown] =
				Events::EventDispatcher<KeyListener&>();

		pressedInputBindings[keyDown].Register(keyEvent);
	}
	void onKeyUp(const std::string keyUp, Events::EventCallback<KeyListener&> keyEvent)
	{
		if (releasedInputBindings.find(keyUp) == releasedInputBindings.end())
			releasedInputBindings[keyUp] =
				Events::EventDispatcher<KeyListener&>();

		releasedInputBindings[keyUp].Register(keyEvent);
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


	void updateKeyDown(KeyListener& input) //Will only get one Key!!
	{
		if (pressedInputs.find(input.keys[0]) != pressedInputs.end())
		{
			for (auto& keypressed : input.keys)
			{
				pressedInputs[keypressed] = input;
			}

			return;
		}

		for (auto& keypressed : input.keys)
		{
			pressedInputs[keypressed] = input;
		}

		std::vector<std::string> keyResults;

		std::unordered_set<std::string> processedKeys;

		std::vector<std::string> inputKeys;
		for (const auto& kv : pressedInputs)
		{
			inputKeys.emplace_back(kv.first.c_str());
		}

		int n = inputKeys.size();
		for (int i = 1; i < (1 << n); ++i)
		{
			std::string combinedKey;
			for (int j = 0; j < n; ++j)
			{
				if (i & (1 << j))
				{
					combinedKey += inputKeys[j];
				}
			}

			// Check if the combined key exists in the map and if it has not been processed
			if (onPressedInputBindings.find(combinedKey) !=
					onPressedInputBindings.end() &&
				processedKeys.find(combinedKey) == processedKeys.end())
			{
				keyResults.push_back(combinedKey);
				processedKeys.insert(
					combinedKey);  // Mark this combined key as processed
			}
		}

		auto keyinputs =
			KeyListener(inputKeys, true, -1,
						-1);  //TODO ook de rest van de inputs er by zetten

		for (const auto& keyInput : keyResults)
		{
			onPressedInputBindings[keyInput].Dispatch(keyinputs);
		}


	}

	void updateKeyUp(KeyListener& input)//Will only get one Key!!
	{
		for (auto& keypressed : input.keys)
		{
			pressedInputs.erase(keypressed);
			releasedInputBindings[keypressed].Dispatch(input);
		}
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
		std::vector<std::string> keyResults;

		std::unordered_set<std::string> processedKeys;

		std::vector<std::string> inputKeys;
		for (const auto& kv : pressedInputs)
		{
			inputKeys.emplace_back(kv.first.c_str());
		}

		int n = inputKeys.size();
		for (int i = 1; i < (1 << n); ++i)
		{	
			std::string combinedKey;
			for (int j = 0; j < n; ++j)
			{
				if (i & (1 << j))
				{  
					combinedKey += inputKeys[j];
				}
			}

			// Check if the combined key exists in the map and if it has not been processed
			if (pressedInputBindings.find(combinedKey) !=
					pressedInputBindings.end() &&
				processedKeys.find(combinedKey) == processedKeys.end())
			{
				keyResults.push_back(combinedKey);
				processedKeys.insert(
					combinedKey);  // Mark this combined key as processed
			}
		}

		auto keyinputs = KeyListener(inputKeys, true, -1,-1); //TODO ook de rest van de inputs er by zetten

		for (const auto& keyInput : keyResults)
		{
			pressedInputBindings[keyInput].Dispatch(keyinputs);
		}
		
	}

private:
	static InputManager instance;

	std::map<std::string, KeyListener> pressedInputs; //Miss kan dit een vector zijn van alle inputs keys dus de strings

	std::map<std::string, Events::EventDispatcher<KeyListener&>>
		onPressedInputBindings;

	std::map<std::string, Events::EventDispatcher<KeyListener&>>
		pressedInputBindings;

	std::map<std::string, Events::EventDispatcher<KeyListener&>>
		releasedInputBindings;



	std::vector<Events::EventDispatcher<KeyListener&>> updateEvents; //miss moet dit weg



	//old

	std::map<int, Events::EventDispatcher<MouseListener&>> buttonDownInputMapping;
	std::map<int, Events::EventDispatcher<MouseListener&>> buttonUpInputMapping;

	Events::EventDispatcher<MouseListener&> mouseMovement{};
	Events::EventDispatcher<WheelListener&> mouseWheelMovement{};
};
