#include "CoinsComponent.hpp"

CoinComponent::CoinComponent(Scene& scene, const std::string& fontName, const Math::Vector2& startPos, 
	const Math::Vector2& scale, Player& player) : IView(scene, fontName)
{
	_coinCounter = std::shared_ptr<GameObject>{ _scene.Instantiate({ startPos, 0.0f, scale }) };
	_coinCounter->AddComponent<Ui::Image>(SPRITE);
	_coinCounter->AddComponent<Ui::Text>(std::to_string(_coins), fontName, 10, DEFAULT_COLOR);
	player.AddCoinObserver([this](int coins) { this->CoinsChanged(coins); });
}

void CoinComponent::CoinsChanged(int coins)
{
	_coins += coins;
	_coinCounter->GetComponent<Ui::Text>().SetText(std::to_string(_coins));
}
