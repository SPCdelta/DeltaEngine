#pragma once

#include "Engine/Delta.hpp"

#include "../../Player.hpp"
#include "../IView.hpp"
#include "BarComponent.hpp"

#include <string>

class HealthBarComponent : public BarComponent
{
public:
	HealthBarComponent(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, const Math::Vector2& scale, Player* player);

private:
	void InitValues(Player* player) override;

	static constexpr const char* SPRITE = "health_bar";
};

