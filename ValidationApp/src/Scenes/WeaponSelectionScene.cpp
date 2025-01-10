#include "WeaponSelectionScene.hpp"

void WeaponSelectionScene::OnStart()
{
	auto vp = GetWindow()->GetViewport();
	std::shared_ptr<GameObject> menu{ Instantiate({{0.0f, 0.0f}, 0.0f, {vp.width, vp.height}}) };
	menu->AddComponent<Ui::Image>("main_menu_bg")->SetLayer(Layer::Background);

	Json::json& data = RetrieveUserData();
	std::string levelName = data["levelName"];
	_weaponSelectionView = std::make_unique<WeaponSelectionView>(
		*this, "goblin", Math::Vector2{0, 0},
		Math::Vector2{600, 600}, levelName);
}
