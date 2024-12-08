#include "Item.hpp"

Item::Item(std::string name, const std::string& spriteName) : _name{name}, _sprite{spriteName} {}

const std::string& Item::GetName() const
{
	return _name;
}

std::string Item::GetSprite()
{
	return _sprite;
}
