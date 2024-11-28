#include "SpeedPotion.hpp"

void SpeedPotion::Use() {
	// huidige speed opslaan
	int currSpeed = _player.GetSpeed(); 

	// speed met meer of minder dan 50% versnellen 
	int newSpeed = _player.GetSpeed() * 2;

	for (int i = static_cast<int>(_time); i > 0; --i)
	{
		
		_player.SetSpeed(newSpeed);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	// oude snelheidswaarde weer herstellen
	_player.SetSpeed(currSpeed);
}
