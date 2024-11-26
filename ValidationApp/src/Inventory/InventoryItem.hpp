#pragma once
#include "../Items/Item.hpp"
class InventoryItem : public Item
{
   public:
	void AddAmount(int amount);
	void LowerAmount(int amount);
	int GetAmount();
   private:
	int amount;
	Item item;
};
