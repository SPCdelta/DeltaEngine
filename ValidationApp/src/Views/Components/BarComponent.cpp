#include "BarComponent.hpp"

BarComponent::BarComponent(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, const Math::Vector2& scale,
	Player& player, const std::string& spriteName) : IView(scene, fontName, startPos, scale), _spriteName{spriteName}
{
	InitBarFg(player);
	InitBarBg();
	InitText(startPos, player);
}

void BarComponent::ValueChanged(int value)
{
	auto diff = _value - static_cast<float>(value);
	_value = value;
	_barFg->transform->scale.AddX(-_unit * diff);
	UpdateText();
}

const Math::Vector2& BarComponent::GetSize() const
{
	return _scale;
}

void BarComponent::InitText(const Math::Vector2& pos, Player& player)
{
	_text = std::shared_ptr<GameObject>{ _scene.Instantiate({ pos, 0.0f, _scale }) };
	auto* text = _text->AddComponent<Ui::Text>("", _fontName, static_cast<int>(_scale.Magnitude() * TEXT_SCALE), DEFAULT_COLOR);
	_text->transform->position.AddY(-Font::GetFontSize(text->GetFont(), text->GetText()).GetY());
}

void BarComponent::UpdateText()
{
	_text->GetComponent<Ui::Text>().SetText(std::to_string(_maxValue) + "/" + std::to_string(_value));
}

void BarComponent::InitBarBg()
{
	_barBg = std::shared_ptr<GameObject>{ _scene.Instantiate({ _pos, 0.0f, _scale }) };
	_barBg->AddComponent<Ui::Image>(DEFAULT_BAR);
}

void BarComponent::InitBarFg(Player& player)
{
	_barFg = std::shared_ptr<GameObject>{ _scene.Instantiate({ _pos, 0.0f, _scale }) };
	_barFg->AddComponent<Ui::Image>(_spriteName);
}
