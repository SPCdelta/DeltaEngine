#pragma once

#include "Engine/Delta.hpp"
#include "../../Player.hpp"
#include "../IView.hpp"
#include <string>
#include <memory>
#include "BarComponent.hpp"

class CoinComponent : public IView
{
public:
	CoinComponent(Scene& scene, const std::string& fontName, const Math::Vector2& startPos,
		const Math::Vector2& scale, Player& player);
	void CoinsChanged(int coins);
private:
	std::shared_ptr<GameObject> _coinCounter;
	size_t _coins = 0;
	static constexpr const char* SPRITE = "coin";
};

