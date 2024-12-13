#include "Inventory.hpp"

Inventory::Inventory() {}

void Inventory::AddItem(std::shared_ptr<Item> item, int amount) 
{
	if (_items.size() == 0 && !IsFull())
	{
		_items.emplace_back(item, amount);
		return;
	}

	bool itemFound = false;
	for (size_t i = 0; i < _items.size(); i++)
	{
		if (_items[i].GetItem()->GetName() == item->GetName())
		{
			_items[i].AddAmount(amount);
			itemFound = true;
			break;
		}
	}

	if (!itemFound && !IsFull())
	{
		_items.emplace_back(item, amount);
	}
}

void Inventory::RemoveItem(const Item& item, int amount)
{
	if (_items.size() <= 0)
	{
		return;
	}

	for (size_t i = 0; i < _items.size(); i++)
	{
		if (*_items[i].GetItem() == item)
		{
			if (amount < _items[i].GetAmount())
			{
				_items[i].LowerAmount(amount);
			}
			else if (amount >= _items[i].GetAmount())
			{
				_items[i].LowerAmount(amount);
				_items.erase(
					std::remove_if(
						_items.begin(), _items.end(),
						[&](const InventoryItem& elem) {
							return *elem.GetItem() == item;
						}),
					_items.end());
			}
			
			return;
		}
		else
		{
			std::cout << "Item not found" << std::endl;
		}
	}
}

int Inventory::GetItemAmount()
{
	return _items.size();
}

InventoryItem& Inventory::GetItem(int index)
{
	return _items[index];
}

void Inventory::Clear()
{
	_items.clear();
}

size_t Inventory::GetSize() const
{
	return _items.size();
}

size_t Inventory::GetCapacity() const
{
	return MAX_SIZE;
}

bool Inventory::IsFull() const
{
	return _items.size() == MAX_SIZE;
}
