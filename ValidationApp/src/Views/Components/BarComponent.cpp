#include "BarComponent.hpp"

BarComponent::BarComponent(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, const Math::Vector2& scale,
	Player& player, const std::string& spriteName) : IView(scene, fontName), _spriteName{spriteName}, _scale{scale}
{
	InitFrame(startPos);

	// TODO: Values are hardcoded for now...
	auto barStartPos = startPos.AddX(60);
	barStartPos.AddY(10);
	_scale.AddX(-120);
	_scale.AddY(-20);

	InitBarFg(barStartPos, player);
	InitBarBg(barStartPos);
}

void BarComponent::ValueChanged(int value)
{
	auto diff = _value - static_cast<float>(value);
	_value = value;
	_barFg->transform->scale.AddX(-_unit * diff);
}

void BarComponent::InitFrame(const Math::Vector2& startPos)
{
	_frame = _scene.Instantiate({ startPos, 0.0f, _scale });
	_frame->AddComponent<Ui::Image>(DEFAULT_FRAME);
}

void BarComponent::InitBarBg(const Math::Vector2& startPos)
{
	_barBg = _scene.Instantiate({ startPos, 0.0f, _scale });
	_barBg->AddComponent<Ui::Image>(DEFAULT_BAR);
}

void BarComponent::InitBarFg(const Math::Vector2& startPos, Player& player)
{
	_barFg = _scene.Instantiate({ startPos, 0.0f, _scale });
	_barFg->AddComponent<Ui::Image>(_spriteName);
}
