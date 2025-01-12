#pragma once

#include "Engine/Delta.hpp"

#include "Item.hpp"

class Coin : public Item
{
   public:
	   Coin(const std::string& name, const std::string& spriteName);

	   std::unique_ptr<Item> Clone() const override;
	   const std::string GetType() const override;
};
