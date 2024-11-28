#include "AttackUpPotion.hpp"


void AttackUpPotion::Use() {
	// oude aanvalsschade (of snelheid?) opslaan
	int currDamage = _player.GetAttackDamage();

	int newDamage = currDamage + 0.75 * currDamage;

	// nieuwe berekenen
	for (int i = static_cast<int>(_time); i > 0; --i)
	{
		_player.SetAttackDamage(newDamage);
		std::cout << _player.GetAttackDamage() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	_player.SetAttackDamage(currDamage);
}
