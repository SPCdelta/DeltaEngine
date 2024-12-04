#pragma once

#include "Engine/Delta.hpp"
#include "../Views/MenuView.hpp"

class DevScene : public Scene
{
public:
	DevScene(const std::string& name) : Scene{name}
	{
		MenuView menuView{ *this, "Dev Menu", 8, "Assets\\Fonts\\knight_warrior.otf", {500, 100}, {200, 50}, 10, 20 };
		menuView.SetButtonText(0, "GameScene");
		menuView.SetButtonText(1, "LayerScene");
		menuView.SetButtonText(2, "PhysicsScene");
		menuView.SetButtonText(7, "Back");
		menuView.SetButtonOnLeftMouseClickLoadScene(0, *this, "GameScene", "GameScene");
		menuView.SetButtonOnLeftMouseClickLoadScene(1, *this, "LayerScene", "LayerScene");
		menuView.SetButtonOnLeftMouseClickLoadScene(2, *this, "PhysicsScene", "PhysicsScene");
		menuView.SetButtonOnLeftMouseClickLoadScene(7, *this, "MainMenuScene", "MainMenuScene");
	}
};