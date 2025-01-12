#include "HealingPotion.hpp"

#include "../../Utils/PotionTypeUtils.hpp"

HealingPotion::HealingPotion(float time, float value, std::string name, std::string sprite) 
	: Potion(time, value, name, sprite) 
{

}

void HealingPotion::Use(Player& player)
{
	if (player.GetHealth() != player._maxHealth)
	{
		int newHealth = player.GetHealth() + static_cast<int>(_value);
		if (newHealth > player._maxHealth)
			player.SetHealth(player._maxHealth);
		else
			player.SetHealth(newHealth);
	}
}

std::unique_ptr<Item> HealingPotion::Clone() const
{
	return std::make_unique<HealingPotion>(*this);
}

PotionType HealingPotion::GetPotionType() const
{
	return PotionType::Healing;
}
