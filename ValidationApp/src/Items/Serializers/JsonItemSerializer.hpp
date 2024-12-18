#pragma once

#include "IItemSerializer.hpp"
#include "Engine/Delta.hpp"

class JsonItemSerializer : public IItemSerializer<JsonItemSerializer, Json::json>
{
public:
	static Json::json Serialize(Item& item);
	static std::unique_ptr<Item> Deserialize(const Json::json& data);
};

