#pragma once

#include <memory>
#include "Engine/Delta.hpp"
#include "InventoryItem.hpp"
#include "../Items/Item.hpp"

class Inventory
{
   public:
	Inventory();
	void AddItem(Item* item, int amount);
	void RemoveItem(const Item& item, int amount);

	int GetItemAmount();
	InventoryItem& GetItem(int index);

	void Clear();
	size_t GetSize() const;
	size_t GetCapacity() const;

   private:
	bool IsFull() const;
	std::vector<InventoryItem> _items;
	const Uint8 MAX_SIZE = 9;
};
