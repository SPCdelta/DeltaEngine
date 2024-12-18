#include "InventoryItem.hpp"

InventoryItem::InventoryItem(Item* item, Uint8 amount) : _item{item}, _amount{amount} {}

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

std::unique_ptr<Item> InventoryItem::GetItem()
{
    return std::move(_item);
}

const Item& InventoryItem::GetItem() const
{
	return *_item.get();
}

InventoryItem::InventoryItem(const InventoryItem& other)
    : _item(other._item->Clone()), _amount(other._amount)
{
}

InventoryItem& InventoryItem::operator=(const InventoryItem& other)
{
    if (this != &other)
    {
        _item = std::unique_ptr<Item>(other._item->Clone());
        _amount = other._amount;
    }
    return *this;
}

InventoryItem::InventoryItem(InventoryItem&& other) noexcept
    : _item(std::move(other._item)), _amount(other._amount)
{
    other._amount = 0;
}

InventoryItem& InventoryItem::operator=(InventoryItem&& other) noexcept
{
    if (this != &other)
    {
        _item = std::move(other._item);
        _amount = other._amount;
        other._amount = 0;
    }
    return *this;
}