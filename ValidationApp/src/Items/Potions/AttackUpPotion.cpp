#include "AttackUpPotion.hpp"


void AttackUpPotion::Use() {
	// oude aanvalsschade (of snelheid?) opslaan

	// nieuwe berekenen
	for (int i = 1; i < static_cast<int>(time); ++i)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		// nieuwe aanvalswaard op de speler toevoegen
	}


}
