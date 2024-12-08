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
protected:
	void InitFrame(const Math::Vector2& startPos);
	void InitBarBg(const Math::Vector2& startPos);
	void InitBarFg(const Math::Vector2& startPos, Player& player);
	virtual void InitValues(Player& player) = 0;
	std::shared_ptr<GameObject> _frame;
	std::shared_ptr<GameObject> _barBg;
	std::shared_ptr<GameObject> _barFg;
	std::string _spriteName;
	int _maxValue;
	Math::Vector2 _scale;
	int _value;
	float _unit; // unit represents the amount of units for each hitpoint lost to reduce the healthbar width.
	// DEFAULT_FRAME & DEFAULT_BAR should be changed to be customizable in the future.
	const std::string DEFAULT_FRAME = "bar_frame";
	const std::string DEFAULT_BAR = "bar";
};

