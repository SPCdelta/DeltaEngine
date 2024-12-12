#pragma once

#include <string>
#include "Item.hpp"
#include "../Player.hpp"

class ConsumableItem : public Item
{
public:
	ConsumableItem(const std::string& name, const std::string& spriteName);
	virtual void Use(Player& player) = 0;
	/// <summary>
	/// 0 = finished, 1 = continue, 2 = finished and marked for removal
	/// </summary>
	/// <returns></returns>
	virtual bool Update() = 0;
};