#include "HealingPotion.hpp"

void HealingPotion::Use() {
	
	for (int i = static_cast<int>(_time); i > 0; --i)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		// per seconden healht erbij krijgen
	}
}
