#include "ShieldBarComponent.hpp"

ShieldBarComponent::ShieldBarComponent(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, 
	const Math::Vector2& scale, Player& player) : BarComponent(scene, fontName, startPos, scale, player, SPRITE)
{
	InitValues(player);
}

void ShieldBarComponent::InitValues(Player& player)
{
	player.AddShieldObserver([this](int shield) { this->ValueChanged(shield); });

	_maxValue = 100; // we set max shield to 100 since it has not been defined.
	_value = player.GetShield();
	_unit = _scale.GetX() / _maxValue;
	_barFg->transform->scale.SetX(_value * _unit);
}
