#include "SpeedPotion.hpp"

void SpeedPotion::Use(Player player) {
	// huidige speed opslaan
	int currSpeed = player.GetSpeed(); 

	// speed met meer of minder dan 50% versnellen 
	int newSpeed = currSpeed * 2;

	float elapsed_time = 0.0f;
	const float potionDuration = _time;

	while (elapsed_time < potionDuration)
	{
		float remainingTime = potionDuration - elapsed_time;
		std::cout << "Potion effect active: " << remainingTime << std::endl;
		elapsed_time += Time::GetDeltaTime();
	}

	// oude snelheidswaarde weer herstellen
	player.SetSpeed(currSpeed);
	std::cout << "Potion effect worn off" << std::endl;
}
