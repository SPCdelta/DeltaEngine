#pragma once

#include "Engine/Delta.hpp"

#include "Item.hpp"
#include "../Player.hpp"

class ConsumableItem : public Item
{
public:
	ConsumableItem(const std::string& name, const std::string& spriteName);

	virtual void Use(Player& player) = 0;

	// Return true if consumable effect has completed, false if effect is ongoing
	virtual bool Update() = 0;

	virtual std::unique_ptr<Item> Clone() const = 0;

	virtual const std::string GetType() const = 0;
};