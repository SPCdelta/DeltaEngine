#include "AttackUpPotion.hpp"


void AttackUpPotion::Use() {
	// oude aanvalsschade (of snelheid?) opslaan

	// nieuwe berekenen
	for (int i = static_cast<int>(_time); i > 0; --i)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "Er is nog voor " << i << " Seconden aan een aanvalsboost" << std::endl;
	}


}
