#include "InputEventDispatchers.hpp"
#include <algorithm>

void InputEventDispatchers::Add(InputState state, const std::string& inputBinding, const std::string& category, Events::EventCallback<Input&>& Inputevent)
{
	if (allCategories.find(category) == allCategories.end())
		activeCategories.insert(category);

	allCategories.insert(category);
	inputBindingCategory[inputBinding] = category;

	if (!Find(state, inputBinding))
		inputBindings[state][inputBinding] = Events::EventDispatcher<Input&>();

	inputBindings[state][inputBinding].Register(Inputevent);
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

void InputEventDispatchers::Remove(InputState state, const std::string& inputBinding, const std::string& category, Events::EventCallback<Input&> regesterd) {
	inputBindings[state][inputBinding].Unregister(regesterd);
}
