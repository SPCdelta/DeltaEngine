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

	size_t GetItemAmount();
	std::shared_ptr<InventoryItem> GetItem(size_t  index);

	void Clear();

   private:
	std::vector<std::shared_ptr<InventoryItem>> _items;
};
