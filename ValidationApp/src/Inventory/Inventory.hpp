#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "InventoryItem.hpp"

class Inventory
{
   public:
	Inventory();
	//~Inventory();

	void AddItem(Item item, int amount);
	void RemoveItem(Item item, int amount);
	void PrintInventory();
	int GetItemAmount();

   private:
	std::vector<std::shared_ptr<InventoryItem>> _items;
};
