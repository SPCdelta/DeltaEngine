#pragma once

#include "Engine/Delta.hpp"
#include "../Items/Item.hpp"

class InventoryItem
{
   public:
	InventoryItem(std::shared_ptr<Item> item, Uint8 amount);
	void AddAmount(Uint8 amount);
	void LowerAmount(Uint8 amount);
	Uint8 GetAmount() const;

	Item* GetItem() const;

   private:
	Uint8 _amount;
	std::shared_ptr<Item> _item;
};
