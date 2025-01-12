#include "Weapon.hpp"

Weapon::Weapon(BehaviourScript* user) 
	: _user{user}
{
	user->onMouseMove(
	[this](Input& e)
	{
		_mouseX = e.mouseX;
		_mouseY = e.mouseY;
	});
}

Weapon ::~Weapon()
{
	_user = nullptr;
}

Math::Vector2 Weapon::GetAimDirection() const
{ 
	return _user->transform->position.DirectionTo(_user->camera->ScreenToWorldPoint({_mouseX, _mouseY}));
}