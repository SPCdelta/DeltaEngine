#include "DefensePotion.hpp"

void DefensePotion::Use(Player& player) {
	if (IsActive)
	{
		std::cout << "Potion already active!" << std::endl;
		return;
	}

	_affectedPlayer = &player;
	_originalShield = player.GetShield();


	int newShield = _originalShield + _originalShield * _value;

	player.SetShield(newShield);
	
	IsActive = true;
	_elapsedTime = 0.0f;
	_potionDuration = _time;

}

void DefensePotion::Update() {
	if (!IsActive)
		return;

	float deltaTime = Time::GetDeltaTime();
	_elapsedTime += deltaTime;

	if (_elapsedTime < _potionDuration)
	{
		float remainingTime = _potionDuration - _elapsedTime;
		std::cout << "Potion effect active: " << remainingTime
				  << " seconds remaining" << std::endl;
	}
	else
	{
		_affectedPlayer->SetShield(_originalShield);
		IsActive = false;
		_affectedPlayer = nullptr;
		std::cout << "Potion effect worn off" << std::endl;
	}
}
