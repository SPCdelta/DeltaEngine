#pragma once

#include "Engine/Delta.hpp"

class PlayerBehaviour : public BehaviourScript
{
public:
	void OnStart() override;
	void OnUpdate() override;

	// Components
	Sprite* sprite = nullptr;
	int test{ 0 };
};