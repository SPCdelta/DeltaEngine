#include "InputEventDispatchers.hpp"
#include "InputHandler.hpp"
#include <algorithm>

void InputEventDispatchers::Add(const InputListener& input)
{
	// Insert if not exists
	if (allCategories.find(input.GetCategory()) == allCategories.end())
		activeCategories.insert(input.GetCategory());

	allCategories.insert(input.GetCategory());
	inputBindingCategory[input.GetInput()] = input.GetCategory();

	if (!Find(input.GetState(), input.GetInput()))
		inputBindings[input.GetState()][input.GetInput()] = Events::EventDispatcher<Input&>();

	inputBindings[input.GetState()][input.GetInput()].Register(input.GetRegistered());
}

bool InputEventDispatchers::DeactivateCategory(const std::string& category)
{
	return activeCategories.erase(category) == 1;
}

bool InputEventDispatchers::DeactivateCategories(
	std::set<std::string> categories)
{
	int countDeactivated = 0;
	for (auto& category : categories)
	{
		countDeactivated += static_cast<int>(activeCategories.erase(category));
	}
	return countDeactivated == categories.size();
}

bool InputEventDispatchers::ActivateCategory(const std::string& category)
{
	if (allCategories.find(category) == allCategories.end())
		return false;

	activeCategories.insert(category);
	return true;
}

bool InputEventDispatchers::ActivateCategories(std::set<std::string> categories)
{
	int countActivated = 0;
	for (auto& category : categories)
	{
		if (allCategories.find(category) != allCategories.end())
		{
			activeCategories.insert(category);
			++countActivated;
		}
	}
	return countActivated == categories.size();
}

bool InputEventDispatchers::Find(InputState state, const std::string& input)
{
	return inputBindings[state].find(input) != inputBindings[state].end();
}

void InputEventDispatchers::DispatchActive(InputState state, const std::string& input, Input inputEvent)
{
	auto it = inputBindingCategory.find(input);

	if (it == inputBindingCategory.end())
		return;

	if (activeCategories.find(it->second) == activeCategories.end())
		return;

	auto eventIt = inputBindings[state].find(input);
	if (eventIt != inputBindings[state].end())
		eventIt->second.Dispatch(inputEvent);
}

void InputEventDispatchers::ExecuteInputsPressedDown(Input allInputs, std::vector<std::string>& strInputs, const std::string&  strPressedDown)
{
	auto it = inputBindings[PressedDown].find(strPressedDown);
	if (it != inputBindings[PressedDown].end())
			DispatchActive(PressedDown, strPressedDown, allInputs);
}

void InputEventDispatchers::ExecuteInputsPressed(Input allInputs, std::vector<std::string>& strInputs)
{
	std::vector<std::string> results;
	std::unordered_set<std::string> processedInputs;

	int n = static_cast<int>(strInputs.size());
	for (int i = 1; i < (1 << n); ++i)
	{
		std::string combinedInput;
		for (int j = 0; j < n; ++j)
		{
			if (i & (1 << j))
			{
				combinedInput += strInputs[j];
			}
		}

		if (Find(Pressed, combinedInput) &&
			processedInputs.find(combinedInput) == processedInputs.end())
		{
			results.push_back(combinedInput);
			processedInputs.insert(combinedInput);
		}
	}

	for (const auto& input : results)
	{
		DispatchActive(Pressed, input, allInputs);
	}
}

void InputEventDispatchers::Remove(InputListener* input) {
	inputBindings[input->GetState()][input->GetInput()].Unregister(input->GetRegistered());
}
