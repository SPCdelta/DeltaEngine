#include "SpeedPotion.hpp"

void SpeedPotion::Use(Player player) {
	// huidige speed opslaan
	int currSpeed = player.GetSpeed(); 

	// speed met meer of minder dan 50% versnellen 
	int newSpeed = currSpeed * 2;

	for (int i = static_cast<int>(_time); i > 0; --i)
	{
		
		player.SetSpeed(newSpeed);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	// oude snelheidswaarde weer herstellen
	player.SetSpeed(currSpeed);
}
