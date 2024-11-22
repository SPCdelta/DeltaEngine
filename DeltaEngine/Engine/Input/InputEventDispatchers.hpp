#pragma once

#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <string>
#include "../Core/Events/EventDispatcher.hpp"
#include "DeltaInputs.hpp"

struct InputLocation
{
	std::string input;
	InputState state;
	std::string category;
	Events::EventCallback<Input&> regesterd;
};


class InputEventDispatchers
{
   public:
	void add(std::string inputBinding, std::string category,
					  Events::EventCallback<Input&> Inputevent);

	bool find(std::string input);
	void dispatchActive(std::string input, Input inputEvent);


	bool deactivateCategory(std::string category);
	bool deactivateCategories(std::set<std::string> categories);
	bool activateCategory(std::string category);
	bool activateCategories(std::set<std::string> categories);

	void executeInputsPressedDown(Input allInputs,
								  std::vector<std::string> strInputs,
								  std::string strPressedDown);
	void executeInputsPressed(Input allInputs, std::vector<std::string> strInputs);
   
	void remove(InputLocation inputLoc);

private:
	std::set<std::string> allCategories;
	std::set<std::string> activeCategories;

	std::map<std::string, std::string> inputBindingCategory;
	std::map<std::string, Events::EventDispatcher<Input&>> inputBindings;
};
