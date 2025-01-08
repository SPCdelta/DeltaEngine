#pragma once

#include "Engine/Delta.hpp"

#include "../Potions/Potion.hpp"

class PotionFactory
{
public:
	static std::unique_ptr<Potion> CreatePotion(const std::string& type, float time, const std::string& sprite, const std::string& name, float value);
	static Json::json ToJson(const Potion& potion);
};
