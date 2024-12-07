#pragma once

#include "Item.hpp"

class WorldItem
{
   public:
	WorldItem(Item item, int amount) : _item(item), _amount(amount) {};

	int _amount;
	Item _item;
};
