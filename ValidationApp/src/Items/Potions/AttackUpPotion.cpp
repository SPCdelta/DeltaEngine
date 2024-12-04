#include "AttackUpPotion.hpp"

void AttackUpPotion::Use(Player& player) {
	if (IsActive)
	{
		std::cout << "Potion already active!" << std::endl;
		return;
	}

	_affectedPlayer = &player;
	_originalDamage = player.GetAttackDamage();

	int newDamage = _originalDamage + _value * _originalDamage;

	player.SetAttackDamage(newDamage);

	IsActive = true;
	_elapsedTime = 0.0f;
	_potionDuration = _time;

}

void AttackUpPotion::Update() {
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
		_affectedPlayer->SetAttackDamage(_originalDamage);
		IsActive = false;
		_affectedPlayer = nullptr;
		std::cout << "Potion effect worn off" << std::endl;
	}
}
