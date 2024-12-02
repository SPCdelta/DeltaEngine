#include "DefensePotion.hpp"

void DefensePotion::Use(Player player) {

	int currShield = player.GetShield();


	int newShield = currShield + currShield * 0.40;

	player.SetShield(newShield);
	

	float elapsed_time = 0.0f;
	const float potionDuration = _time;

	while (elapsed_time < potionDuration)
	{
		float remainingTime = potionDuration - elapsed_time;
		std::cout << "Potion effect active: " << remainingTime << std::endl;
		elapsed_time += Time::GetDeltaTime();
	}

	player.SetShield(currShield);
	std::cout << "Potion effect worn off" << std::endl;

}
