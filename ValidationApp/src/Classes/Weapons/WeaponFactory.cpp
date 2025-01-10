#include "WeaponFactory.hpp"
#include "../../Utils/WeaponTypeUtils.hpp"
#include "Bow.hpp"
#include "Gun.hpp"
#include "Boomerang.hpp"

std::unique_ptr<Weapon> WeaponFactory::CreateWeapon(const std::string& type, BehaviourScript* user)
{
	switch (WeaponTypeUtils::FromString(type))
	{
	case WeaponType::Bow:
		return std::make_unique<Bow>(user);
	case WeaponType::Gun:
		return std::make_unique<Gun>(user);
	case WeaponType::Boomerang:
		return std::make_unique<Boomerang>(user);
	default:
		throw std::invalid_argument("Could not create weapon from data.");
	}
}