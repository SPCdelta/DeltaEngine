#include "HealingPotion.hpp"

void HealingPotion::Use(Player player) 
{
	if (player.GetHealth() == player._maxHealth)
	{
		// doe hier iets	
	}
	else
	{
		player.SetHealth(player._maxHealth);
	}
}
