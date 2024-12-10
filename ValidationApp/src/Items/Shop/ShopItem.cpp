#include "ShopItem.hpp"

ShopItem::ShopItem(int price, int amount, Item item)
	: _price{price}, _amount{amount}, _item{item}
{}

void ShopItem::LowerAmount(int amount) {
	if (_amount - amount < 0)
		this->_amount = 0;
	else
		this->_amount -= amount;
}

void ShopItem::AddAmount(int amount) {
	_amount += amount;
}

int ShopItem::GetPrice() const
{
	return _price;
}

int ShopItem::GetAmount() const
{
	return _amount;
}

Item& ShopItem::GetItem()
{
	return _item;
}
