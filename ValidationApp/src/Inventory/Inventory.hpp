#pragma once

#include <unordered_map>
#include "Engine/Delta.hpp"
#include "InventoryItem.hpp"
#include "../Items/Item.hpp"

class Inventory
{
public:
	Inventory();
	void AddItem(Item* item, Uint8 amount);
	Item* RemoveItem(const Item& item, Uint8 amount);

	Uint8 GetItemAmount(Uint8 index) const;
	const std::optional<InventoryItem>& GetItem(Uint8 index) const;
	std::optional<InventoryItem>& GetItem(Uint8 index);

	void Clear();
	Uint8 GetSize() const;
	Uint8 GetCapacity() const;

private:
	bool IncreaseAmount(const Item& item, Uint8& amount);
	bool Insert(Item* item, Uint8& amount);
	bool IsFull() const;
	static const Uint8 MAX_SIZE = 9;
	std::array<std::optional<InventoryItem>, MAX_SIZE> _items;
	Uint8 _size = 0;
};
