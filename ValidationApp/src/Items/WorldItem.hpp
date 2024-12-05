#pragma once

#include "Item.hpp"

class WorldItem : public Item
{
   public:
	int amount;
	Item item;
};
