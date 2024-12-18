#include "AttackUpPotion.hpp"

PotionType AttackUpPotion::GetPotionType() const
{
	return PotionType::AttackUp;
}

void AttackUpPotion::Use(Player& player)
{
	if (IsActive)
	{
		std::cout << "Potion already active!" << std::endl;
		return;
	}

	_affectedPlayer = &player;
	_originalDamage = player.GetAttackDamage();

	float newDamage = _originalDamage + _value * _originalDamage;

	player.SetAttackDamage(newDamage);

	IsActive = true;
	_elapsedTime = 0.0f;
	_potionDuration = _time;

}

bool AttackUpPotion::Update()
{
	if (!IsActive)
		return true;

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
	return false;
}

std::unique_ptr<Item> AttackUpPotion::Clone() const
{
	return std::make_unique<AttackUpPotion>(*this);
}
