#pragma once

#include "Engine/Delta.hpp"
#include "../Views/WeaponSelectionView.hpp"

class WeaponSelectionScene : public Scene
{
public:
	WeaponSelectionScene(const std::string& sceneName);

	void OnStart() override;

private:
	std::unique_ptr<WeaponSelectionView> _weaponSelectionView;
};