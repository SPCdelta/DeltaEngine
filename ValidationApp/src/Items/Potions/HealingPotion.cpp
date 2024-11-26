#include "HealingPotion.hpp"

HealingPotion::HealingPotion(float time, float value) : Potion(time, value) {}

void HealingPotion::Use() {
	
	for (int i = 1; i < static_cast<int>(time); ++i)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		// per seconden healht erbij krijgen
	}
}
