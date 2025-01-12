#pragma once

#include "Engine/Delta.hpp"

#include "../Classes/IPrototype.hpp"

class Item : IPrototype<Item>
{
public:
	Item(const std::string& name, const std::string& spriteName);
	virtual ~Item() = default;
	
	bool operator==(const Item& other) const;

	const std::string& GetName() const;
	const std::string& GetSprite() const;

	virtual std::unique_ptr<Item> Clone() const = 0;

	virtual const std::string GetType() const = 0;

private:
	std::string _name;
	std::string _sprite;
};
