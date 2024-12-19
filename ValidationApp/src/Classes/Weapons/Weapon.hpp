#pragma once

#include <Engine/Delta.hpp>

class Weapon
{
public:
	Weapon(BehaviourScript* user) : _user{ user }
	{ 
		user->onMouseMove([this](Input& e)
		{ 
			_mouseX = e.mouseX;
			_mouseY = e.mouseY;
		});
	}

	~Weapon()
	{
		_user = nullptr;
	}

	virtual void Use() = 0;

	Math::Vector2 GetAimDirection() const
	{ 
		return _user->transform->position.DirectionTo(_user->camera->ScreenToWorldPoint({_mouseX, _mouseY})); //TODO je kan nu ook InputManager::getMouse krijgen
		//InputManager::GetMousePosition(); <---
	}

protected:
	BehaviourScript* _user;

private:
	int _mouseX = 0;
	int _mouseY = 0;
};