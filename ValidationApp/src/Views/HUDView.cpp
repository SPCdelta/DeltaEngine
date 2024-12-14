#include "HUDView.hpp"

HUDView::HUDView(Scene& scene, const std::string& fontName, Player& player) : IView(scene, fontName),
	_player(player)
{
	InitShieldBar();
	InitHealthBar();
	InitHotbar();
	InitCoinCounter();
}

// TODO: make absolute positions relative
void HUDView::InitHotbar()
{
	_hotbar = std::make_unique<HotbarComponent>(
		_scene, 
		NUM_OF_COLS,
		_fontName,
		Math::Vector2{ 340, 620 },
		Math::Vector2{ 100, 100 },
		_player);
}

void HUDView::InitHealthBar()
{
	_healthBar = std::make_unique<HealthBarComponent>(
		_scene,
		_fontName,
		Math::Vector2{ 340, 550 },
		Math::Vector2{ 600, 30 },
		_player
	);
}

void HUDView::InitShieldBar()
{
	_shieldBar = std::make_unique<ShieldBarComponent>(
		_scene,
		_fontName,
		Math::Vector2{ 340, 580 },
		Math::Vector2{ 600, 30 },
		_player
	);
}

void HUDView::InitCoinCounter()
{
	_coinCounter = std::make_unique<CoinComponent>(
		_scene, 
		_fontName, 
		Math::Vector2{ 1000, 650 },
		Math::Vector2{ 50, 50 },
		_player
	);
}