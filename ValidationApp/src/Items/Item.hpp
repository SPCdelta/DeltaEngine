#pragma once

#include <string>

class Item
{
   public:
	Item(const std::string& name, const std::string& spriteName);
	//virtual ~Item() = default;
	virtual void kek() {};

	const std::string& GetName() const;

	bool operator==(const Item& other) const
	{
		return this->GetName() == other.GetName();
	}

	const std::string& GetSprite() const;

   private:
	std::string _name;
	std::string _sprite;
};
