#pragma once

#include <memory>
#include "Engine/Delta.hpp"
#include "Components/HealthBarComponent.hpp"
#include "Components/HotbarComponent.hpp"
#include "Components/ShieldBarComponent.hpp"
#include "IView.hpp"
#include <string>
#include "Components/CoinsComponent.hpp"

class HUDView : public IView
{
public:
	HUDView(Scene& scene, const std::string& fontName, Player& player);
private:
	void InitHotbar();
	void InitHealthBar();
	void InitShieldBar();
	void InitCoinCounter();
	void InitGameSpeed();
	std::unique_ptr<HotbarComponent> _hotbar;
	std::unique_ptr<HealthBarComponent> _healthBar;
	std::unique_ptr<ShieldBarComponent> _shieldBar;
	std::unique_ptr<CoinComponent> _coinCounter;
	const Uint8 NUM_OF_COLS = 6;
	Player& _player;
};

