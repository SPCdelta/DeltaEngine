#pragma once

#include <Engine/Delta.hpp>

class Weapon
{
public:
	Weapon(BehaviourScript* user);
	~Weapon();

	virtual void Use() = 0;

	Math::Vector2 GetAimDirection() const;

protected:
	BehaviourScript* _user;

private:
	int _mouseX = 0;
	int _mouseY = 0;
};