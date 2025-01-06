#include "HUDView.hpp"

HUDView::HUDView(Scene& scene, const std::string& fontName, Player* player) : IView(scene, fontName, {}, {}),
	_player(player)
{
	// DO NOT CHANGE INITIALISATION ORDER
	InitHotbar();
	InitShieldBar();
	InitHealthBar();
	InitCoinCounter();
}

const Math::Vector2& HUDView::GetSize() const
{
	// TODO: insert return statement here
	return _scale;
}

void HUDView::InitHotbar()
{
	auto vp = _scene.GetWindow()->GetViewport();
	Math::Vector2 slotScale = Math::Vector2{ 100, 100 };
	float xPos = (vp.width / 2) - ((NUM_OF_COLS * slotScale.GetX()) / 2);
	float yPos = vp.height - slotScale.GetY();
	_hotbar = std::make_unique<HotbarComponent>(
		_scene,
		NUM_OF_COLS,
		_fontName,
		Math::Vector2{ xPos, yPos },
		slotScale,
		_player);
}

void HUDView::InitHealthBar()
{
	auto vp = _scene.GetWindow()->GetViewport();
	float size = vp.width * vp.height * BAR_YSCALE;
	Math::Vector2 scale = { _hotbar->GetSize().GetX() / 2, size };
	float marginY = -scale.GetY() * BAR_MY_SCALE;
	float xPos = _hotbar->GetPos().GetX();
	float yPos = _hotbar->GetPos().GetY() - scale.GetY() + marginY;
	_healthBar = std::make_unique<HealthBarComponent>(
		_scene,
		_fontName,
		Math::Vector2{ xPos, yPos },
		scale,
		_player
	);
}

void HUDView::InitShieldBar()
{
	auto vp = _scene.GetWindow()->GetViewport();
	float size = vp.width * vp.height * BAR_YSCALE;
	Math::Vector2 scale = { _hotbar->GetSize().GetX() / 2, size };
	float marginY = -scale.GetY() * BAR_MY_SCALE;
	float xPos = _hotbar->GetPos().GetX() + scale.GetX();
	float yPos = _hotbar->GetPos().GetY() - scale.GetY() + marginY;
	_shieldBar = std::make_unique<ShieldBarComponent>(
		_scene,
		_fontName,
		Math::Vector2{ xPos, yPos },
		scale,
		_player
	);
}

void HUDView::InitCoinCounter()
{
	auto vp = _scene.GetWindow()->GetViewport();
	Math::Vector2 scale = { COIN_SIZE, COIN_SIZE };
	float margin = COIN_SIZE * COIN_MARGIN_SCALE;
	float xPos = _hotbar->GetSize().GetX() + _hotbar->GetPos().GetX() + margin;
	float yPos = vp.height - COIN_SIZE - margin;
	_coinCounter = std::make_unique<CoinComponent>(
		_scene, 
		_fontName, 
		Math::Vector2{ xPos, yPos },
		scale,
		_player
	);
}