#pragma once

#include "Engine/Delta.hpp"
#include "../../Player.hpp"
#include "../IView.hpp"
#include <string>

class BarComponent : public IView
{
public:
	BarComponent(Scene& scene, const std::string& fontName, const Math::Vector2& startPos,
		const Math::Vector2& scale, Player& player, const std::string& spriteName);
	void ValueChanged(int value);
	const Math::Vector2& GetSize() const override;
protected:
	void InitBarBg();
	void InitBarFg(Player& player);
	void InitText(Player& player);
	virtual void InitValues(Player& player) = 0;
	void UpdateText();
	std::shared_ptr<GameObject> _text;
	std::shared_ptr<GameObject> _barBg;
	std::shared_ptr<GameObject> _barFg;
	std::string _spriteName;
	int _maxValue;
	int _value;
	float _unit; // unit represents the amount of units for each hitpoint lost to reduce the healthbar width.
	// DEFAULT_BAR should be changed to be customizable in the future.
	const std::string DEFAULT_BAR = "bar";
	const float TEXT_SCALE = 0.05f;
};

