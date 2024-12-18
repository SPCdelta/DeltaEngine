#include "SpeedPotion.hpp"

PotionType SpeedPotion::GetPotionType() const
{
	return PotionType::Speed;
}

void SpeedPotion::Use(Player& player) {
	if (IsActive)
	{
		std::cout << "Potion already active!" << std::endl;
		return;
	}	
	
	// huidige speed opslaan
	_affectedPlayer = &player;
	_originalSpeed = player.GetSpeed(); 

	// speed met meer of minder dan 50% versnellen 
	float newSpeed = _originalSpeed * _value;

	player.SetSpeed(newSpeed);
	
	IsActive = true;
	_elapsedTime = 0.0f;
	_potionDuration = _time;

}

bool SpeedPotion::Update() {
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
		_affectedPlayer->SetSpeed(_originalSpeed);
		IsActive = false;
		_affectedPlayer = nullptr;
		std::cout << "Potion effect worn off" << std::endl;
	}
	return false;
}

std::unique_ptr<Item> SpeedPotion::Clone() const
{
	return std::make_unique<SpeedPotion>(*this);
}
