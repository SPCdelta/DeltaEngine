#include "Item.hpp"

Item::Item(const std::string& name, const std::string& spriteName) : _name{name}, _sprite{spriteName} {}

const std::string& Item::GetName() const
{
	return _name;
}

const std::string& Item::GetSprite() const
{
	return _sprite;
}
