#include "HealingPotion.hpp"

void HealingPotion::Use(Player& player) 
{
	std::cout << "Current Health: " << player.GetHealth() << std::endl;
	if (player.GetHealth() != player._maxHealth)
	{
		int newHealth = player.GetHealth() + _value;
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
