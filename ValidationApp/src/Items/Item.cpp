#include "Item.hpp"

Item::Item(std::string name) : _name{name} {} // hier komt sprite nog bij

const std::string& Item::GetName() const
{
	return _name;
}
