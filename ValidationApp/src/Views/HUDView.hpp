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
	const Math::Vector2& GetSize() const override;
private:
	void InitHotbar();
	void InitHealthBar();
	void InitShieldBar();
	void InitCoinCounter();
	std::unique_ptr<HotbarComponent> _hotbar;
	std::unique_ptr<HealthBarComponent> _healthBar;
	std::unique_ptr<ShieldBarComponent> _shieldBar;
	std::unique_ptr<CoinComponent> _coinCounter;
	const Uint8 NUM_OF_COLS = 9;
	Player& _player;
	const float HOTBAR_SCALE = 0.0001f;
	const float BAR_YSCALE = 0.00003f;
	const float BAR_MY_SCALE = 0.33f;
	const float COIN_SIZE = 50.f;
	const float COIN_MARGIN_SCALE = 0.5f;
};

