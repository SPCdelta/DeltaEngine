#include "SpeedPotion.hpp"

void SpeedPotion::Use() {
	// huidige speed opslaan
	// speed met meer of minder dan 50% versnellen 

	for (int i = 1; i < static_cast<int>(time); ++i)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "Je hebt nu nog " << i << " Seconden een snelheidsboost"
				  << std::endl;
	}

	// oude snelheidswaarde weer herstellen
}
