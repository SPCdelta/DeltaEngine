#include "DefensePotion.hpp"

void DefensePotion::Use() {

	int currShield = _player.GetShield();


	int newShield = currShield + currShield * 0.40;

	for (int i = static_cast<int>(_time); i > 0 ; --i)
	{
		_player.SetShied(newShield);  
		std::this_thread::sleep_for(std::chrono::seconds(1));

	}

	_player.SetShied(currShield);

}
