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
		menuView.SetButtonOnLeftMouseClick(0, [this]() -> void
			{
				LoadScene("GameScene");
			}, "dev_menu_buttons");
		menuView.SetButtonOnLeftMouseClick(1, [this]() -> void
			{
				LoadScene("LayerScene");
			}, "dev_menu_buttons");
		menuView.SetButtonOnLeftMouseClick(2, [this]() -> void
			{
				LoadScene("PhysicsScene");
			}, "dev_menu_buttons");
		menuView.SetButtonOnLeftMouseClick(7, [this]() -> void
			{
				LoadScene("MainMenuScene");
			}, "dev_menu_buttons");
	}
};