#pragma once

#include "Engine/Delta.hpp"

#include "../Items/Potions/PotionType.hpp"

#include <unordered_map>

class PotionTypeUtils
{
public:
	static const std::string ToString(PotionType type);
	static PotionType FromString(const std::string& type);

private:
    static const std::unordered_map<PotionType, std::string> _potionTypes;
};

