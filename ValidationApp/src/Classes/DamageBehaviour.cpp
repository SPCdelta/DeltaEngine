#include "DamageBehaviour.hpp"
#include "../Scripts/EnemyBehaviour.hpp"

DamageBehaviour:: DamageBehaviour(Rigidbody& rigidbody, Sprite& sprite, std::initializer_list<std::string> damageSourceTags) : 
	_rigidbody{ rigidbody }, _sprite{ sprite }, _damageSourceTags{damageSourceTags}, _currentCollider{nullptr}
{
	_ogColor = sprite.GetColor();

	_rigidbody.onTriggerEnter.Register([this](Collider& collider)
	{ 
		if (collider.transform.gameObject && IsDamageSource(collider.transform.gameObject->GetTag()) && collider.transform.gameObject->GetComponent<Sprite>().GetVisible())
		{
			_damageCount = 1; 
			_currentCollider = std::make_shared<Collider>(collider);
		}		
	});

	_rigidbody.onTriggerExit.Register([this](Collider& collider)
	{
		if (collider.transform.gameObject && IsDamageSource(collider.transform.gameObject->GetTag()) && collider.transform.gameObject->GetComponent<Sprite>().GetVisible())
		{
			_damageCount = 0;
			_currentCollider = nullptr; 
		}	
	});
}

DamageBehaviour::~DamageBehaviour()
{
	_currentCollider = nullptr;
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

int DamageBehaviour::TakeDamage()
{
	int damage = 0;
	if (_currentCollider && _currentCollider->transform.gameObject  && _currentCollider->transform.gameObject->GetComponent<Sprite>().GetVisible())
	{	
		if (_currentCollider->transform.gameObject->GetTag() == "projectile" || _currentCollider->transform.gameObject->GetTag() == "skeleton_arrow") 
		{
			auto& projectile = _currentCollider->transform.gameObject->GetComponent<Projectile>();
			damage = projectile.GetProjectileData().damage;
        } 
		else if (_currentCollider->transform.gameObject->GetTag() == "goblin" || _currentCollider->transform.gameObject->GetTag() == "slime") 
		{
			auto& enemy = _currentCollider->transform.gameObject->GetComponent<EnemyBehaviour>().GetEnemy();
            damage = enemy.GetDamage(); 
        }

		StartInvincibility();
		_sprite.SetColor(Rendering::Color(255.0f, 0.0f, 0.0f, 1.0f));	
	}
	else
	{
		_damageCount = 0;
		_currentCollider = nullptr;	 
	}

	return damage;
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
