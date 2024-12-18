#include "HealingPotion.hpp"
#include "../../Utils/PotionTypeUtils.hpp"

void HealingPotion::Use(Player& player)
{
	std::cout << "Current Health: " << player.GetHealth() << std::endl;
	if (player.GetHealth() != player._maxHealth)
	{
		int newHealth = player.GetHealth() + static_cast<int>(_value);
		if (newHealth > player._maxHealth)
		{
			player.SetHealth(player._maxHealth);
		}
		else
		{
			player.SetHealth(newHealth);
		}
	}
	std::cout << "New health: " << player.GetHealth() << std::endl;
}

std::unique_ptr<Item> HealingPotion::Clone() const
{
	return std::make_unique<HealingPotion>(*this);
}

PotionType HealingPotion::GetPotionType() const
{
	return PotionType::Healing;
}

