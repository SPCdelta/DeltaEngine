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

	void AddItem(const Item& item, int amount);
	void RemoveItem(const Item& item, int amount);
	void PrintInventory();

	int GetItemAmount();
	std::shared_ptr<InventoryItem> GetItem(int index);

	void Clear();

   private:
	std::vector<std::shared_ptr<InventoryItem>> _items;
};
