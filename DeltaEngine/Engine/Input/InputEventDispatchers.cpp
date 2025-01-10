#include "InputEventDispatchers.hpp"
#include "InputHandler.hpp"
#include <algorithm>

void InputEventDispatchers::Add(InputListener* input)
{
	std::cout << input->GetType() + ": " << input->GetState() + ": " << input->GetInput() << "\n";
	inputBindings[input->GetState()][input->GetInput()].Register(input->GetRegistered());
}

bool InputEventDispatchers::Find(InputState state, const std::string& input)
{
	return inputBindings[state].find(input) != inputBindings[state].end();
}

void InputEventDispatchers::DispatchActive(InputState state, const std::string& input, Input inputEvent)
{
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
