#pragma once

#include <Engine/Delta.hpp>
#include "WeaponType.hpp"

class Weapon
{
public:
	Weapon(BehaviourScript* user);
	~Weapon();

	virtual void Use() {};
	virtual void Update(float deltaTime) {};
	virtual WeaponType GetWeaponType() const
	{
		return WeaponType::Weapon;
	}

	Math::Vector2 GetAimDirection() const;

protected:
	BehaviourScript* _user;
	int _mouseX = 0;
	int _mouseY = 0;
	float _attackCooldown = 1.f;
	float _timeSinceLastAttack = 0.f;
};