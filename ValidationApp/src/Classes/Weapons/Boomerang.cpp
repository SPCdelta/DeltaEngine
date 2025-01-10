#include "Boomerang.hpp"
#include "../../Scripts/BoomerangBehaviour.hpp"

Boomerang::Boomerang(BehaviourScript* user) : Weapon{user}
{

}

void Boomerang::Use()
{
	if (_boomerang)
		return;

	std::shared_ptr<GameObject> boomerangObj = _user->transform->gameObject->Instantiate();
	_boomerang = boomerangObj->AddComponent<BoomerangBehaviour>();

	Math::Vector2 throwDirection = 
		_user->transform->position.DirectionTo(_user->transform->gameObject->GetCamera()->ScreenToWorldPoint(_mouseX, _mouseY));

	_boomerang->Throw(_user->transform->gameObject, 15.0f, _user->transform->gameObject->transform->position, throwDirection);

	_boomerang->onFinish.Register([this, boomerangObj](Events::Event e)
		{
			_user->transform->gameObject->Destroy();
			_boomerang = nullptr;
		});
}

WeaponType Boomerang::GetWeaponType() const
{
	return WeaponType::Boomerang;
}
