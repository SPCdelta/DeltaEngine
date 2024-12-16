#pragma once

#include <string>
#include "Item.hpp"
#include "../Player.hpp"

class ConsumableItem : public Item
{
public:
	ConsumableItem(const std::string& name, const std::string& spriteName);
	virtual void Use(Player& player) = 0;
	// return true if consumable effect has completed, false if effect is ongoing
	virtual bool Update() = 0;
};