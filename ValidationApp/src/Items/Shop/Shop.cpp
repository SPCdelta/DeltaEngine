#include "Shop.hpp"


Shop::Shop(Inventory inventory) : _inventory(inventory) {}

void Shop::Buy() {
	
}

void Shop::Sell() {
	
}

void Shop::Add(int price, int amount, const ShopItem& item)
{
	if (_shopItems.size() == 0)
	{
		_shopItems.push_back(std::make_shared<ShopItem>(price, amount, item));
		return;
	}

	bool itemFound = false;
	for (size_t i = 0; i < _shopItems.size(); i++)
	{
		if (_shopItems[i]->GetItem().GetName() == item.GetName())
		{
			_shopItems[i]->AddAmount(amount);
			itemFound = true;
			break;
		}
	}

	if (!itemFound)
	{
		_shopItems.push_back(std::make_shared<ShopItem>(price, amount, item));
	}
}

void Shop::Remove(const ShopItem& item, int amount) {
	if (_shopItems.size() <= 0)
		return;

	for (size_t i = 0; i < _shopItems.size(); i++)
	{
		if (amount < _shopItems[i]->GetAmount())
		{
			_shopItems[i]->LowerAmount(amount);
		}
		else
		{
			_shopItems[i]->LowerAmount(amount);
			_shopItems.erase(
				std::remove_if(_shopItems.begin(), _shopItems.end(),
							   [&](const std::shared_ptr<ShopItem>& elem)
							   { return elem->GetItem() == item; }),
				_shopItems.end()); 
		}
		
		return;
	}
	else
	{
		std::cout << "Item not found" << std::endl;
	}
}

