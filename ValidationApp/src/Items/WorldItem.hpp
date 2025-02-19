#pragma once

#include <memory>

#include "Item.hpp"

class WorldItem
{
public:
	WorldItem(Item* item, int amount);
	~WorldItem() = default;

	WorldItem(const WorldItem& other);
	WorldItem& operator=(const WorldItem& other);
	WorldItem(WorldItem&& other) noexcept;
	WorldItem& operator=(WorldItem&& other) noexcept;
	
	int _amount;
	std::unique_ptr<Item> _item;
};
