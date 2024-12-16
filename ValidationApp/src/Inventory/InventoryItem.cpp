#include "InventoryItem.hpp"

InventoryItem::InventoryItem(std::shared_ptr<Item> item, Uint8 amount) : _item{item}, _amount{amount} {}

void InventoryItem::AddAmount(Uint8 amount)
{
	this->_amount += amount;
}

void InventoryItem::LowerAmount(Uint8 amount)
{
	if (_amount - amount < 0)
		this->_amount = 0;
	else
		this->_amount -= amount;
}

Uint8 InventoryItem::GetAmount() const
{
	return _amount;
}

Item* InventoryItem::GetItem() const
{
	return _item.get();
}
