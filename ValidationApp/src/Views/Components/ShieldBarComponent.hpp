#pragma once

#include "Engine/Delta.hpp"
#include "../../Player.hpp"
#include "../IView.hpp"
#include <string>
#include "BarComponent.hpp"

class ShieldBarComponent : public BarComponent
{
public:
	ShieldBarComponent(Scene& scene, const std::string& fontName, const Math::Vector2& startPos,
		const Math::Vector2& scale, Player* player);
private:
	void InitValues(Player* player) override;
	static constexpr const char* SPRITE = "shield_bar";
};


