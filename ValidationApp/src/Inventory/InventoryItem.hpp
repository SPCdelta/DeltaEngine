#pragma once

#include "Engine/Delta.hpp"
#include "../Items/Item.hpp"

class InventoryItem
{
   public:
	InventoryItem(Item* item, Uint8 amount);
	InventoryItem(const InventoryItem& other);
	InventoryItem& operator=(const InventoryItem& other);
	InventoryItem(InventoryItem&& other) noexcept;
	InventoryItem& operator=(InventoryItem&& other) noexcept;
	~InventoryItem() = default;
	void AddAmount(Uint8 amount);
	void LowerAmount(Uint8 amount);
	Uint8 GetAmount() const;
	std::unique_ptr<Item> GetItem();
	const Item& GetItem() const;

   private:
	Uint8 _amount;
	std::unique_ptr<Item> _item;
};
