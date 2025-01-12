#pragma once

#include "Engine/Delta.hpp"

#include "../ConsumableItem.hpp"
#include "../../Player.hpp"
#include "../../Utils/PotionTypeUtils.hpp"
#include "PotionType.hpp"

class Potion : public ConsumableItem
{
public:
	Potion(float time, float value, const std::string& name, const std::string& spriteName);

	virtual void Use(Player& player) = 0;

	virtual bool Update() 
	{ 
		return true; 
	};

	virtual std::unique_ptr<Item> Clone() const = 0;

	float GetTime() const;
	float GetValue() const;

	virtual const std::string GetType() const
	{
		return std::string{TYPE + ':' + PotionTypeUtils::ToString(GetPotionType())};
	}

protected:
	float _time;
	float _value;
	virtual PotionType GetPotionType() const = 0;

private:
	const std::string TYPE = "potion";
};
