#include "HealingPotion.hpp"

void HealingPotion::Use(Player player) 
{
	std::cout << "Current Health: " << player.GetHealth() << std::endl;
	if (player.GetHealth() == player._maxHealth)
	{
		std::cout << "Already max health" << std::endl;	
	}
	else
	{
		player.SetHealth(player._maxHealth);
	}

	std::cout << "New health: " << player.GetHealth() << std::endl;
}
