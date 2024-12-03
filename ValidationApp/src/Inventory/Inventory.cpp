#include "Inventory.hpp"

Inventory::Inventory() {}

void Inventory::AddItem(Item item, int amount) {
	if (_items.size() == 0)
	{
		_items.push_back(std::make_shared<InventoryItem>(item, amount));
		return;
	}

	bool itemFound = false;

	for (size_t i = 0; i < _items.size(); i++)
	{
		if (_items[i]->GetItem().GetName() == item.GetName())
		{
			_items[i]->AddAmount(amount);
			itemFound = true;
			break;
		}
	}

	if (!itemFound)
	{
		_items.push_back(std::make_shared<InventoryItem>(item, amount));
	}

}

void Inventory::RemoveItem(Item item, int amount)
{
	if (_items.size() <= 0)
	{
		return;
	}

	for (size_t i = 0; i < _items.size(); i++)
	{
		if (_items[i]->GetItem().GetName() == item.GetName())
		{
			if (amount < _items[i]->GetAmount())
			{
				_items[i]->LowerAmount(amount);
			}
			else if (amount >= _items[i]->GetAmount())
			{
				_items[i]->LowerAmount(amount);
				_items.erase(
					std::remove_if(
						_items.begin(), _items.end(),
						[&](const std::shared_ptr<InventoryItem>& elem) {
							return elem->GetItem().GetName() == item.GetName();
						}),
					_items.end());
			}
		}
		else
		{
			std::cout << "Item not found" << std::endl;
		}
	}
}

void Inventory::PrintInventory() {
	if (_items.size() == 0)
	{
		std::cout << "Inventory is empty" << std::endl;
		return;
	}

	for (size_t i = 0; i < _items.size(); i++)
	{
		std::cout << _items[i]->GetItem().GetName() << " "
				  << _items[i]->GetAmount() << std::endl;
	}
}
