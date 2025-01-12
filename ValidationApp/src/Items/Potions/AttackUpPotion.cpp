#include "AttackUpPotion.hpp"

AttackUpPotion::AttackUpPotion(float time, float value, std::string name, std::string sprite) 
	: Potion(time, value, name, sprite)
{

}

PotionType AttackUpPotion::GetPotionType() const
{
	return PotionType::AttackUp;
}

void AttackUpPotion::Use(Player& player)
{
	if (IsActive)
		return;

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
	}
	else
	{
		_affectedPlayer->SetAttackDamage(_originalDamage);
		IsActive = false;
		_affectedPlayer = nullptr;
	}

	return false;
}

std::unique_ptr<Item> AttackUpPotion::Clone() const
{
	return std::make_unique<AttackUpPotion>(*this);
}
