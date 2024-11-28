#include "DefensePotion.hpp"

void DefensePotion::Use(Player player) {

	int currShield = player.GetShield();


	int newShield = currShield + currShield * 0.40;

	for (int i = static_cast<int>(_time); i > 0 ; --i)
	{
		player.SetShield(newShield);  
		std::this_thread::sleep_for(std::chrono::seconds(1));

	}

	player.SetShield(currShield);

}
