#pragma once

#include <string>

class Item
{
   public:
	Item(std::string name);
	virtual ~Item() = default;

	const std::string& GetName() const;

	bool operator==(const Item& other) const
	{
		return this->GetName() == other.GetName();
	}

	std::string GetSprite();

   private:
	std::string _name;
	std::string sprite;
};
