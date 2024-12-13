#pragma once

#include <memory>
#include "../Items/Item.hpp"

class InventoryItem
{
   public:
	InventoryItem(std::shared_ptr<Item> item, int amount);
	void AddAmount(int amount);
	void LowerAmount(int amount);
	int GetAmount() const;

	Item* GetItem() const;

   private:
	int _amount;
	std::shared_ptr<Item> _item;
};
