#include "DefensePotion.hpp"

PotionType DefensePotion::GetPotionType() const
{
	return PotionType::Defense;
}

void DefensePotion::Use(Player& player) {
	if (IsActive)
	{
		std::cout << "Potion already active!" << std::endl;
		return;
	}

	_affectedPlayer = &player;
	_originalShield = player.GetShield();


	int newShield = _originalShield + 1 * static_cast<int>(_value);

	newShield = newShield > MAX_SHIELD ? 100 : newShield;

	player.SetShield(newShield);
	
	IsActive = true;
	_elapsedTime = 0.0f;
	_potionDuration = _time;

}

bool DefensePotion::Update() {
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
		_affectedPlayer->SetShield(_originalShield);
		IsActive = false;
		_affectedPlayer = nullptr;
		std::cout << "Potion effect worn off" << std::endl;
	}
	return false;
}

std::unique_ptr<Item> DefensePotion::Clone() const
{
	return std::make_unique<DefensePotion>(*this);
}
