#pragma once

#include <memory>
#include "Engine/Delta.hpp"
#include "InventoryItem.hpp"
#include "../Items/Item.hpp"

class Inventory
{
   public:
	Inventory();
	void AddItem(std::shared_ptr<Item> item, Uint8 amount);
	void RemoveItem(const Item& item, Uint8 amount);

	Uint8 GetItemAmount(Uint8 index) const;
	InventoryItem& GetItem(Uint8 index);

	void Clear();
	Uint8 GetSize() const;
	Uint8 GetCapacity() const;

   private:
	bool IsFull() const;
	std::vector<InventoryItem> _items;
	const Uint8 MAX_SIZE = 9;
};
