#include "CoinsComponent.hpp"

CoinComponent::CoinComponent(Scene& scene, const std::string& fontName, const Math::Vector2& pos, const Math::Vector2& scale, Player* player) 
	: IView(scene, fontName, pos, scale), 
	  _coins(player->GetCoins())
{
	_coinCounter = std::shared_ptr<GameObject>{ _scene.Instantiate({ pos, 0.0f, scale }) };
	_coinCounter->AddComponent<Ui::Image>(SPRITE);
	_coinCounter->AddComponent<Ui::Text>(std::to_string(_coins), fontName, 10, DEFAULT_COLOR)
		->SetPosition(_coinCounter->GetComponent<Ui::Text>().GetPosition() + Math::Vector2{0.0f, -10.0f});
	player->AddCoinObserver([this](int coins) { this->CoinsChanged(coins); });
}

void CoinComponent::CoinsChanged(int coins)
{
	_coins += coins;
	_coinCounter->GetComponent<Ui::Text>().SetText(std::to_string(_coins));
}

const Math::Vector2& CoinComponent::GetSize() const
{
	return _scale;
}
