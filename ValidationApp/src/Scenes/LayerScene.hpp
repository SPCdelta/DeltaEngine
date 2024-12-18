#pragma once

#include <memory>

#include "Engine/Delta.hpp"

#include "../Scripts/PlayerBehaviour.hpp"
#include "../Scripts/EnemyBehaviour.hpp"
#include "../Items/Potions/HealingPotion.hpp"
#include "../Views/HUDView.hpp"

class LayerScene : public Scene
{
   public:
	LayerScene(const std::string& sceneName) : Scene(sceneName){};

	void OnStart() override;

private:
	std::unique_ptr<HUDView> _hud;
};
