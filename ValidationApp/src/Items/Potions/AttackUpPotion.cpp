#include "AttackUpPotion.hpp"

void AttackUpPotion::Use(Player player) {
	// oude aanvalsschade (of snelheid?) opslaan
	int currDamage = player.GetAttackDamage();

	int newDamage = currDamage + 0.75 * currDamage;

	player.SetAttackDamage(newDamage);

	float elapsed_time = 0.0f;
	const float potionDuration = _time;

	while (elapsed_time < potionDuration)
	{
		float remainingTime = potionDuration - elapsed_time;
		std::cout << "Potion effect active: " << remainingTime << std::endl;
		elapsed_time += Time::GetDeltaTime();
		
	}
	
	player.SetAttackDamage(currDamage);
	std::cout << "Potion effect worn off" << std::endl;
}
