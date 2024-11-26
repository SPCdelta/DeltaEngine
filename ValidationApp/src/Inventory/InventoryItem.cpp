#include "InventoryItem.hpp"

void InventoryItem::AddAmount(int amount) {
	this->amount += amount;
}

void InventoryItem::LowerAmount(int amount) {
	this->amount -= amount;
}

int InventoryItem::GetAmount()
{
	return amount;
}
