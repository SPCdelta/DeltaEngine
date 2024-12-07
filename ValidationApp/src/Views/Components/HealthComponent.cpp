#include "HealthComponent.hpp"

HealthComponent::HealthComponent(Scene& scene, const Math::Vector2& startPos, const Math::Vector2& scale, 
	Player& player)
{
	InitFrame(scene, startPos, scale);

	auto barStartPos = startPos.AddX(60);
	barStartPos.AddY(10);
	auto barScale = scale.AddX(-120);
	barScale.AddY(-20);

	InitBarFg(scene, barStartPos, barScale, player);
	InitBarBg(scene, barStartPos, barScale);
}

void HealthComponent::HealthChanged(int health)
{	
	auto diff = _health - static_cast<float>(health);
	_health = health;
	_barFg->transform->scale.AddX(-_unit * diff);
}

void HealthComponent::InitFrame(Scene& scene, const Math::Vector2& startPos, const Math::Vector2& scale)
{
	_frame = std::shared_ptr<GameObject>{ scene.Instantiate({ startPos, 0.0f, scale }) };
	_frame->AddComponent<Ui::Image>("bar_frame");
}

void HealthComponent::InitBarBg(Scene& scene, const Math::Vector2& startPos, const Math::Vector2& scale)
{
	_barBg = std::shared_ptr<GameObject>{ scene.Instantiate({ startPos, 0.0f, scale }) };
	_barBg->AddComponent<Ui::Image>("bar");
}

void HealthComponent::InitBarFg(Scene& scene, const Math::Vector2& startPos, const Math::Vector2& scale, Player& player)
{
	_barFg = std::shared_ptr<GameObject>{ scene.Instantiate({ startPos, 0.0f, scale }) };
	_barFg->AddComponent<Ui::Image>("health_bar");

	player.AddHealthObserver([this](int health) { this->HealthChanged(health); });

	_maxHealth = player._maxHealth;
	_health = player.GetHealth();
	_unit = scale.GetX() / _maxHealth;
	_barFg->transform->scale.SetX(_health * _unit);
}
