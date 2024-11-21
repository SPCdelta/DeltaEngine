#include "InputEventDispatchers.hpp"
#include <algorithm>

void InputEventDispatchers::add(std::string inputBinding, std::string category,
								Events::EventCallback<Input&> Inputevent)
{
	if (allCategories.find(category) == allCategories.end())
		activeCategories.insert(category);

	allCategories.insert(category);
	inputBindingCategory[inputBinding] = category;

	if (!find(inputBinding))
		inputBindings[inputBinding] = Events::EventDispatcher<Input&>();

	inputBindings[inputBinding].Register(Inputevent);
}

bool InputEventDispatchers::deactivateCategory(std::string category)
{
	return activeCategories.erase(category) == 1;
}

bool InputEventDispatchers::deactivateCategories(
	std::set<std::string> categories)
{
	int countDeactivated = 0;
	for (auto& category : categories)
	{
		countDeactivated += activeCategories.erase(category);
	}
	return countDeactivated == categories.size();
}

bool InputEventDispatchers::activateCategory(std::string category)
{
	if (allCategories.find(category) == allCategories.end())
		return false;

	activeCategories.insert(category);
	return true;
}

bool InputEventDispatchers::activateCategories(std::set<std::string> categories)
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

bool InputEventDispatchers::find(std::string input)
{
	return inputBindings.find(input) != inputBindings.end();
}

void InputEventDispatchers::dispatchActive(std::string input, Input inputEvent)
{
	auto it = inputBindingCategory.find(input);

	if (it == inputBindingCategory.end())
		return;

	if (activeCategories.find(it->second) == activeCategories.end())
		return;

	auto eventIt = inputBindings.find(input);
	if (eventIt != inputBindings.end())
		eventIt->second.Dispatch(inputEvent);
}

void InputEventDispatchers::executeInputsPressedDown(
	Input allInputs, std::vector<std::string> strInputs,  std::string strPressedDown)
{
	for (const auto& pair : inputBindings)
	{
		if (pair.first.find(strPressedDown) == std::string::npos)
			continue;

		for (auto& letter : pair.first)
		{
			if (std::find(strInputs.begin(), strInputs.end(), letter + "") ==
				strInputs.end())
				break; 
		}
		dispatchActive(strPressedDown, allInputs);
	}
}

void InputEventDispatchers::executeInputsPressed(
	Input allInputs, std::vector<std::string> strInputs)
{
	std::vector<std::string> results;
	std::unordered_set<std::string> processedInputs;

	int n = strInputs.size();
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

		if (find(combinedInput) &&
			processedInputs.find(combinedInput) == processedInputs.end())
		{
			results.push_back(combinedInput);
			processedInputs.insert(combinedInput);
		}
	}

	for (const auto& input : results)
	{
		dispatchActive(input, allInputs);
	}
}