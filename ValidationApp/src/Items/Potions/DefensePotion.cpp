#include "DefensePotion.hpp"

void DefensePotion::Use() {
	// originele defense stat onthouden

	// eventueel nieuwe defense stat berekenen, zoals plus 50%
	for (int i = static_cast<int>(_time); i > 0 ; --i)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		// nieuwe defense stat voor de speler tot de tijd op is
	}

	// originele stat weer herstellen
}
