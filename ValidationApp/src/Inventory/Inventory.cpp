#include "Inventory.hpp"

Inventory::Inventory() {}

void Inventory::AddItem(Item item, int amount) {

	std::cout << "Checking if i already have this item" << std::endl;

	if (_items.size() > 0)
	{
		for (size_t i = 0; i < _items.size(); i++)
		{
			if (_items[i]->GetItem().GetName() == item.GetName())
			{
				std::cout << "Item found, adding to existing amount!"
						  << std::endl;
				_items[i]->AddAmount(amount);
			}
		}
	}
	else
	{
		std::cout << "adding item to my inventory!" << std::endl;
		_items.push_back(std::make_shared<InventoryItem>(item, amount));
	}

}

void Inventory::RemoveItem(Item item, int amount)
{
	if (_items.size() > 0)
	{
		for (size_t i = 0; i < _items.size(); i++)
		{
			if (_items[i]->GetItem().GetName() == item.GetName())
			{
				if (amount < _items[i]->GetAmount())
				{
					std::cout << "Lowering the amount of the item" << std::endl;
					_items[i]->LowerAmount(amount);
				}
				else if (amount == _items[i]->GetAmount())
				{
					std::cout << "The same amount of items exists in the "
								 "inventory, so it will be deleted"
							  << std::endl;

					_items[i]->LowerAmount(amount);
					_items.erase(
						std::remove_if(
							_items.begin(), _items.end(),
							[&](const std::shared_ptr<InventoryItem>& elem) {
								return elem->GetItem().GetName() ==
									   item.GetName();
							}),
						_items.end());
				}
				else
				{
					std::cout << "You are trying to remove a higher amount of items than exists in your inventory, so the complete amount of this item will be removed" 
							  << std::endl;
					_items[i]->LowerAmount(_items[i]->GetAmount());
					_items.erase(
						std::remove_if(
							_items.begin(), _items.end(),
							[&](const std::shared_ptr<InventoryItem>& elem) {
								return elem->GetItem().GetName() ==
									   item.GetName();
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
	else
	{
		std::cout << "Inventory is already empty!" << std::endl;
	}
}

void Inventory::PrintInventory() {
	if (_items.size() != 0)
	{
		for (size_t i = 0; i < _items.size(); i++)
		{
			std::cout << _items[i]->GetItem().GetName() << " "
					  << _items[i]->GetAmount() << std::endl;
		}
	}
	else
	{
		std::cout << "Inventory empty" << std::endl;
	}
}
