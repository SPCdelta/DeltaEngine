#pragma once

#include <iostream>
#include "Engine/Delta.hpp"

class TempBehaviour : public BehaviourScript
{
public:
	// Components
	

	// Methods
	void OnStart() override
	{
		//std::cout << "OnStart" << std::endl;
	}

	void OnUpdate() override
	{
		//std::cout << "OnUpdate" << std::endl;
	}
};