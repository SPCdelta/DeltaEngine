#pragma once
#include "../Items/Item.hpp"
class InventoryItem
{
   public:
	InventoryItem(Item item, int amount);
	void AddAmount(int amount);
	void LowerAmount(int amount);
	int GetAmount();
	Item& GetItem();
   private:
	int _amount;
	Item _item;

};
