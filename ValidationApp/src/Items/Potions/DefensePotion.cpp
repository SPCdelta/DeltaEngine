#include "DefensePotion.hpp"

DefensePotion::DefensePotion(float time, float value, std::string name, std::string sprite) 
	: Potion(time, value, name, sprite) 
{

}

PotionType DefensePotion::GetPotionType() const
{
	return PotionType::Defense;
}

void DefensePotion::Use(Player& player) 
{
	if (IsActive)
		return;

	_affectedPlayer = &player;
	_originalShield = player.GetShield();

	int newShield = _originalShield + _originalShield * static_cast<int>(_value);

	player.SetShield(newShield);
	
	IsActive = true;
	_elapsedTime = 0.0f;
	_potionDuration = _time;
}

bool DefensePotion::Update() 
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
		_affectedPlayer->SetShield(_originalShield);
		IsActive = false;
		_affectedPlayer = nullptr;
	}

	return false;
}

std::unique_ptr<Item> DefensePotion::Clone() const
{
	return std::make_unique<DefensePotion>(*this);
}
