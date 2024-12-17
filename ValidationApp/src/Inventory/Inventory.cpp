#include "Inventory.hpp"

Inventory::Inventory() {}

void Inventory::AddItem(Item* item, Uint8 amount)
{
	if (_size == 0)
	{
		_items[0] = InventoryItem(item, amount);
		++_size;
		return;
	}
	if (!IncreaseAmount(*item, amount))
	{
		Insert(item, amount);
	}
}

Item* Inventory::RemoveItem(const Item& item, Uint8 amount)
{
	if (_items.size() <= 0)
	{
		return nullptr;
	}

	for (Uint8 i = 0; i < _items.size(); i++)
	{
		if (_items[i].has_value() && *_items[i]->GetItem() == item)
		{
			if (amount < _items[i]->GetAmount())
			{
				_items[i]->LowerAmount(amount);
			}
			else
			{
				auto* result = _items[i]->GetItem().release();
				_items[i] = std::nullopt;
				--_size;
				return result;
			}
			return nullptr;
		}
	}
	return nullptr;
}

Uint8 Inventory::GetItemAmount(Uint8 index) const
{
	return _items[index]->GetAmount();
}

const std::optional<InventoryItem>& Inventory::GetInventoryItem(Uint8 index) const
{
	return _items[index];
}

std::optional<InventoryItem>& Inventory::GetInventoryItem(Uint8 index)
{
	return _items[index];
}

void Inventory::Clear()
{
	_items.fill(std::nullopt);
}

Uint8 Inventory::GetSize() const
{
	return _size;
}

Uint8 Inventory::GetCapacity() const
{
	return MAX_SIZE;
}

bool Inventory::IncreaseAmount(const Item& item, Uint8& amount)
{
	for (Uint8 i = 0; i < _items.size(); i++)
	{
		const std::optional<InventoryItem>& optItem = _items[i];
		if (optItem.has_value() && optItem->GetItem().GetName() == item.GetName())
		{
			_items[i]->AddAmount(amount);
			return true;
		}
	}
	return false;
}

bool Inventory::Insert(Item* item, Uint8& amount)
{
	for (auto& optItem : _items)
	{
		if (!optItem.has_value())
		{
			optItem = InventoryItem(item, amount);
			++_size;
			return true;
		}
	}
	return false;
}

bool Inventory::IsFull() const
{
	return _size == MAX_SIZE;
}
