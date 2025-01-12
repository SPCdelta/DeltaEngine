#include "JsonItemSerializer.hpp"

#include "../Potions/PotionFactory.hpp"
#include "../../Utils/ItemTypeUtils.hpp"

Json::json JsonItemSerializer::Serialize(Item& item)
{
	if (ItemTypeUtils::GetHeader(item.GetType()) == "potion")
		return PotionFactory::ToJson(*dynamic_cast<Potion*>(&item));
	else
		throw std::exception{ "Could not serialize item from data." };
}

std::unique_ptr<Item> JsonItemSerializer::Deserialize(const Json::json& data)
{
	if (ItemTypeUtils::GetHeader(data["type"]) == "potion")
		return PotionFactory::CreatePotion(data["type"], data["time"], data["sprite"], data["name"], data["value"]);
	else 
		throw std::exception{ "Could not deserialize item from data." };
}
