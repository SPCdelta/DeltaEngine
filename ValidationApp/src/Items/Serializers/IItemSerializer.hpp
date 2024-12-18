#pragma once

#include "../Item.hpp"
#include "Engine/Delta.hpp"

template<typename Derived, typename T>
class IItemSerializer
{
public:
	static T Serialize(Item& item)
	{
		return Derived::Serialize(item);
	}
	static std::unique_ptr<Item> Deserialize(const T& data)
	{
		return Derived::Deserialize(data);
	}
};
