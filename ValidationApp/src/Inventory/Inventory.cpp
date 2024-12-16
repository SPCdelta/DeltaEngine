#include "Inventory.hpp"

Inventory::Inventory() {}

void Inventory::AddItem(std::shared_ptr<Item> item, Uint8 amount)
{
	if (_items.size() == 0 && !IsFull())
	{
		_items.emplace_back(item, amount);
		return;
	}

	bool itemFound = false;
	for (Uint8 i = 0; i < _items.size(); i++)
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

void Inventory::RemoveItem(const Item& item, Uint8 amount)
{
	if (_items.size() <= 0)
	{
		return;
	}

	for (Uint8 i = 0; i < _items.size(); i++)
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

Uint8 Inventory::GetItemAmount(Uint8 index) const
{
	return _items[index].GetAmount();
}

InventoryItem& Inventory::GetItem(Uint8 index)
{
	return _items[index];
}

void Inventory::Clear()
{
	_items.clear();
}

Uint8 Inventory::GetSize() const
{
	return static_cast<Uint8>(_items.size());
}

Uint8 Inventory::GetCapacity() const
{
	return MAX_SIZE;
}

bool Inventory::IsFull() const
{
	return _items.size() == MAX_SIZE;
}
