#include "AttackUpPotion.hpp"


void AttackUpPotion::Use(Player player) {
	// oude aanvalsschade (of snelheid?) opslaan
	int currDamage = player.GetAttackDamage();

	int newDamage = currDamage + 0.75 * currDamage;

	// nieuwe berekenen
	for (int i = static_cast<int>(_time); i > 0; --i)
	{
		player.SetAttackDamage(newDamage);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	player.SetAttackDamage(currDamage);
}
