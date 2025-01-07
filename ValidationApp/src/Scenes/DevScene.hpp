#pragma once

#include "Engine/Delta.hpp"
#include "../Views/MenuView.hpp"

class DevScene : public Scene
{
public:
	DevScene(const std::string& name) : Scene{name}
	{

	}

	void OnStart() override
	{
		MenuView menuView{ *this, "Dev Menu", 8, "alucrads", {500, 100}, {200, 50}, 10, 40 };
		menuView.SetButtonTextColor(-1, {255, 255, 255, 255});
		menuView.SetButtonText(0, "GameScene");
		menuView.SetButtonText(1, "LayerScene");
		menuView.SetButtonText(2, "PhysicsScene");
		menuView.SetButtonText(7, "Back");
		menuView.AddButtonTextPosition(-1, {20, 5});
		menuView.SetButtonOnLeftMouseClickLoadScene(0, this, "GameScene", "Dev Menu");
		menuView.GetButton(1)->GetComponent<Ui::Button>().SetOnLeftMouseClick([this]() -> void
			{
				Json::json jsonLevelName;
				jsonLevelName["levelName"] = "LayerScene";
				StoreUserData(jsonLevelName);
				LoadScene("WeaponSelectionScene");
			}, "Dev Menu");
		menuView.SetButtonOnLeftMouseClickLoadScene(2, this, "PhysicsScene", "Dev Menu");
		menuView.SetButtonOnLeftMouseClickLoadScene(7, this, "MainMenuScene", "Dev Menu");
	}
};