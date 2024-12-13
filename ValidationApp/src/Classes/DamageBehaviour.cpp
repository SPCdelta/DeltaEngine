#include "DamageBehaviour.hpp"

DamageBehaviour:: DamageBehaviour(Rigidbody& rigidbody, Sprite& sprite, const std::vector<std::string>& damageSourceTags) : 
	_rigidbody{ rigidbody }, _sprite{ sprite }, _damageSourceTags{damageSourceTags}
{
	_ogColor = sprite.GetColor();

	_rigidbody.onTriggerEnter.Register([this](Collider& collider)
	{ 
		if (IsDamageSource(collider.transform.gameObject->GetTag()))
			_damageCount = 1; 
	});

	_rigidbody.onTriggerExit.Register([this](Collider& collider)
	{
		if (IsDamageSource(collider.transform.gameObject->GetTag()))
			_damageCount = 0;
	});
}

DamageBehaviour::~DamageBehaviour()
{
	// TODO unregister events
}

void DamageBehaviour::Update(float deltaTime)
{
	if (_invincibleTime > 0.0f)
	{
		_invincibleTime -= deltaTime;
		if (static_cast<int>(_invincibleTime * 10) % 2 == 0)
			_sprite.SetColor(_ogColor);	 // Normal color
		else
			_sprite.SetColor(Rendering::Color(255.0f, 255.0f, 255.0f, 1.5f)); // Flash effect
	}
	else
	{
		_sprite.SetColor(_ogColor);	 // Reset color after taking damage
	}
}

bool DamageBehaviour::GetDamage() const
{
	return _damageCount > 0 && CanTakeDamage();
}

void DamageBehaviour::TakeDamage()
{
	StartInvincibility();
	_sprite.SetColor(Rendering::Color(255.0f, 0.0f, 0.0f, 1.0f)); 
}

void DamageBehaviour::StartInvincibility()
{
	_invincibleTime = _invincibilityDuration / Time::GetMultiplier();
}

bool DamageBehaviour::CanTakeDamage() const
{
	return _invincibleTime <= 0.0f;
}

bool DamageBehaviour::IsDamageSource(const std::string& tag) const
{
	return std::find(_damageSourceTags.begin(), _damageSourceTags.end(), tag) != _damageSourceTags.end();
}
