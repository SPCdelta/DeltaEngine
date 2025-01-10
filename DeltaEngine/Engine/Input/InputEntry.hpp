#pragma once

#include "InputHelper.hpp"

class InputEntry
{
public:
	InputEntry() 
	{ 
		InputHelper::CreateInput();
	}

	~InputEntry() 
	{ 
		InputHelper::RemoveInput();
	}
};