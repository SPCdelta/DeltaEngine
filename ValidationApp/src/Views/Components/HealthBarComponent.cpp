#include "HealthBarComponent.hpp"

HealthBarComponent::HealthBarComponent(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, 
	const Math::Vector2& scale, Player* player) : BarComponent(scene, fontName, startPos, scale, player, SPRITE)
{
	InitValues(player);
}

void HealthBarComponent::InitValues(Player* player)
{
	player->AddHealthObserver([this](int health) { this->ValueChanged(health); });

	_maxValue = player->_maxHealth;
	_value = player->GetHealth();
	_unit = _scale.GetX() / _maxValue;
	_barFg->transform->scale.SetX(_value * _unit);
	UpdateText();
}


