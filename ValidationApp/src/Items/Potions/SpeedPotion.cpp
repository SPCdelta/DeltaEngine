#include "SpeedPotion.hpp"

SpeedPotion::SpeedPotion(float time, float value, std::string name, std::string sprite)
	: Potion(time, 2.0f, name, sprite)
{

}

PotionType SpeedPotion::GetPotionType() const
{
	return PotionType::Speed;
}

void SpeedPotion::Use(Player& player) 
{
	if (IsActive)
		return;
	
	// Save current speed
	_affectedPlayer = &player;
	_originalSpeed = player.GetSpeed(); 

	// Speed including more or less than 50% acceleration 
	float newSpeed = _originalSpeed * _value;
	player.SetSpeed(newSpeed);
	
	IsActive = true;
	_elapsedTime = 0.0f;
	_potionDuration = _time;
}

bool SpeedPotion::Update() 
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
		_affectedPlayer->SetSpeed(_originalSpeed);
		IsActive = false;
		_affectedPlayer = nullptr;
	}

	return false;
}

std::unique_ptr<Item> SpeedPotion::Clone() const
{
	return std::make_unique<SpeedPotion>(*this);
}
