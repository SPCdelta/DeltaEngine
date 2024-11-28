#include "HealingPotion.hpp"

void HealingPotion::Use() 
{
	for (int i = static_cast<int>(_time); i > 0; --i)
	{
		_player.SetHealth(5);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
