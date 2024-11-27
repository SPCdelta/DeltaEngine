#include "InventoryItem.hpp"

InventoryItem::InventoryItem(Item item, int amount) : _item{item}, _amount{amount} {}

void InventoryItem::AddAmount(int amount)
{
	this->_amount += amount;
}

void InventoryItem::LowerAmount(int amount) {
	this->_amount -= amount;
}

int InventoryItem::GetAmount()
{
	return _amount;
}

Item& InventoryItem::GetItem()
{
	return _item;
}
