#pragma once
#include <vector>
#include "ShopItem.hpp"
#include <memory>
#include "../../Inventory/Inventory.hpp"
class Shop
{
   public:
	Shop(Inventory inventory);
	void Buy();
	void Sell();
	void Add(const ShopItem& item);
	void Remove(const ShopItem& item);
   private:
	std::vector<std::shared_ptr<ShopItem>> _shopItems;
	Inventory _inventory;
};
