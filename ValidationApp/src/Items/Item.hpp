#pragma once
#include <string>

class Item
{
   public:
	std::string GetName();
   private:
	std::string name;
	std::string sprite;
};
