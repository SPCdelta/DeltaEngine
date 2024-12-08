#pragma once

#include "Engine/Delta.hpp"
#include "../../Player.hpp"
#include "../IView.hpp"
#include <string>

class HealthComponent : public IView
{
public:
	HealthComponent(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, 
		const Math::Vector2& scale, Player& player);
	void HealthChanged(int health);
private:
	void InitFrame(const Math::Vector2& startPos, const Math::Vector2& scale);
	void InitBarBg(const Math::Vector2& startPos, const Math::Vector2& scale);
	void InitBarFg(const Math::Vector2& startPos, const Math::Vector2& scale, Player& player);
	std::shared_ptr<GameObject> _frame;
	std::shared_ptr<GameObject> _barBg;
	std::shared_ptr<GameObject> _barFg;
	int _maxHealth;
	int _health;
	float _unit; // unit represents the amount of units for each hitpoint lost to reduce the healthbar width.
};

