#include "Inventory.hpp"

Inventory::Inventory() {}

void Inventory::AddItem(std::shared_ptr<InventoryItem> item, int amount) {
	auto eItem = find(items.begin(), items.end(), item->GetName());

	if (eItem != items.end())
	{
		item->AddAmount(amount);
	}
	else
	{
		items.push_back(item);
		item->AddAmount(amount);
	}
}

void Inventory::RemoveItem(std::shared_ptr<InventoryItem> item, int amount) {
	auto eItem = find(items.begin(), items.end(), item->GetName());

	if (eItem != items.end())
	{
		if (amount < item->GetAmount())
		{
			item->LowerAmount(amount);
		}
		else if (amount == item->GetAmount())
		{
			item->LowerAmount(amount);
			items.erase(eItem);
		}
		else
		{
			std::cout << "Item has not that many items";
		}
	}
	else
	{
		std::cout << "Item not found";	
	}
}
