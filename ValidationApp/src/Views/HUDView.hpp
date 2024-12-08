#pragma once

#include <memory>
#include "Engine/Delta.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/HotbarComponent.hpp"

class HUDView
{
public:
	HUDView();
private:
	void InitHotbar();
	void InitHealthbar();
	std::unique_ptr<HotbarComponent> _hotbar;
	std::unique_ptr<HealthComponent> _healthBar;
};

