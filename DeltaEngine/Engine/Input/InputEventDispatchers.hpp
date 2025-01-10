#pragma once

#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <string>
#include "../Core/Events/EventDispatcher.hpp"
#include "DeltaInputs.hpp"

class InputListener;

class InputEventDispatchers
{
   public:
	void Add(const InputListener& input);
	void Remove(InputListener* input);

	bool Find(InputState state, const std::string& input);
	void DispatchActive(InputState state, const std::string& input, Input inputEvent);


	bool DeactivateCategory(const std::string& category);
	bool DeactivateCategories(std::set<std::string> categories);
	bool ActivateCategory(const std::string& category);
	bool ActivateCategories(std::set<std::string> categories);

	void ExecuteInputsPressedDown(Input allInputs, std::vector<std::string>& strInputs, const std::string& strPressedDown);
	void ExecuteInputsPressed(Input allInputs, std::vector<std::string>& strInputs);
   

private:
	std::set<std::string> allCategories;
	std::set<std::string> activeCategories;

	std::map<std::string, std::string> inputBindingCategory;
	std::map<InputState, std::map<std::string, Events::EventDispatcher<Input&>>> inputBindings;
	
};
