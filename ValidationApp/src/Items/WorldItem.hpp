#pragma once

#include <memory>
#include "Item.hpp"

class WorldItem
{
   public:
	WorldItem(std::shared_ptr<Item> item, int amount);
	int _amount;
	std::shared_ptr<Item> _item;
};
