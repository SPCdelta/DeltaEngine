#pragma once
#include <string>

class Item
{
   public:
	Item(std::string name);
	const std::string& GetName() const;
	bool operator==(const Item& other) const
	{
		return this->GetName() == other.GetName();
	}
   private:
	std::string _name;
	std::string sprite;
};
