#pragma once

#include "Engine/Delta.hpp"

class MainMenuBehaviour : public BehaviourScript
{
public:
	void OnStart() override;
	void OnUpdate() override;

	int test{ 0 };
};