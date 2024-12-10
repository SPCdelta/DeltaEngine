#pragma once
#include "../Item.hpp"

class ShopItem : public Item
{
   public:
	ShopItem(int price, int amount, Item item);
	void LowerAmount(int amount);
	void AddAmount(int amount);

	int GetPrice() const;
	int GetAmount() const;
	Item& GetItem(); 

   private:
	int _price;
	int _amount;
	Item _item;
};
