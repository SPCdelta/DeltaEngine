#include "Coin.hpp"

Coin::Coin(const std::string& name, const std::string& spriteName) 
	: Item{name, spriteName}
{

}

std::unique_ptr<Item> Coin::Clone() const
{
	return std::make_unique<Coin>(*this);
}

const std::string Coin::GetType() const
{
	return "coin";
}