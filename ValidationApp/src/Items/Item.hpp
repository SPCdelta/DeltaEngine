#pragma once

#include <string>

class Item
{
   public:
	Item(std::string name, const std::string& spriteName);
	virtual ~Item() = default;

	const std::string& GetName() const;

	bool operator==(const Item& other) const
	{
		return this->GetName() == other.GetName();
	}

	std::string GetSprite();

   private:
	std::string _name;
	std::string _sprite;
};
