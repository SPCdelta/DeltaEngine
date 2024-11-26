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

	void AddItem(std::shared_ptr<InventoryItem> item, int amount);
	void RemoveItem(std::shared_ptr<InventoryItem> item, int amount);


   private:
	std::vector<std::shared_ptr<InventoryItem>> items;
};
