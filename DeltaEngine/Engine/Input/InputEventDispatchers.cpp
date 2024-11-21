#include "InputEventDispatchers.hpp"

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
