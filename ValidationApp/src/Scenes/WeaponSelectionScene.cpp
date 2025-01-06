#include "WeaponSelectionScene.hpp"

void WeaponSelectionScene::OnStart()
{
	_weaponSelectionView = std::make_unique<WeaponSelectionView>(
		*this, "goblin", Math::Vector2{0, 0},
		Math::Vector2{600, 600});
}
