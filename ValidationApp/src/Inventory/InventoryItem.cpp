#include "InventoryItem.hpp"

InventoryItem::InventoryItem(std::shared_ptr<Item> item, int amount) : _item{item}, _amount{amount} {}

void InventoryItem::AddAmount(int amount)
{
	this->_amount += amount;
}

void InventoryItem::LowerAmount(int amount) 
{
	if (_amount - amount < 0)
		this->_amount = 0;
	else
		this->_amount -= amount;
}

int InventoryItem::GetAmount() const
{
	return _amount;
}

Item* InventoryItem::GetItem() const
{
	return _item.get();
}
