#pragma once

#include "Engine/Delta.hpp"
#include "../Views/MenuView.hpp"

class LevelEditorLevelChose : public Scene
{
public:
	LevelEditorLevelChose(const std::string& name) : Scene(name){}

	void OnStart() override{

		auto allLevels = FileManager::filesInDirectory(LEVEL_PATH);

		Rendering::UnsignInt8 buttonAmount = static_cast<Rendering::UnsignInt8>(allLevels.size()) + 2;

		MenuView menuView{ *this, "Main Menu", buttonAmount, "alucrads", {485, 50}, {300, 100}, 25, 80 };

		std::shared_ptr<GameObject> menu{ Instantiate({{0.0f, 0.0f}, 0.0f, {1280.0f, 720.0f}}) };
		menu->AddComponent<Ui::Image>("main_menu_bg");
		menu->AddComponent<Audio::MusicSource>("Assets\\Audio\\Music\\Intro_Theme.mp3", false, true)->Play();

		menuView.SetTitleTextPosition({ 515, 50 });
		menuView.SetTitleTextColor({ 255, 255, 255, 255 });
		menuView.SetButtonTextColor(-1, { 255, 255, 255, 255 });

		menuView.SetButtonTexture(0, "scroll2");
		menuView.SetButtonPosition(0, { 300, 175 });
		menuView.SetButtonScale(0, { 300, 100 });
		menuView.SetButtonText(0, "Back");
		menuView.AddButtonTextPosition(0, { -150, 10 });


		menuView.SetButtonTexture(1, "scroll2");
		menuView.SetButtonPosition(1, { 650, 175 });
		menuView.SetButtonScale(1, { 300, 100 });
		menuView.SetButtonText(1, "Make New Level");
		menuView.AddButtonTextPosition(1, { 230, -90 });
		menuView.SetButtonTextSize(1, 40);

		//menuView TODO maak h box hier van
		for (int i = 0; i < static_cast<int>(allLevels.size()); i++)
		{
			menuView.AddButtonTextPosition(i + 2, { 45, 0 });
			menuView.SetButtonOnLeftMouseClickLoadScene(i + 2, *this, "LevelEditor", "UI:Editor");
			menuView.SetButtonText(i + 2, allLevels[i]);

		}
		//TODO maak v box hier van
		menuView.SetButtonOnLeftMouseClick(0, [this]() -> void
			{
				LoadScene("MainMenuScene");
			}, "UI:Back");
		menuView.SetButtonOnLeftMouseClick(1, [this]() -> void
			{
				LoadScene("LevelEditor");
			}, "UI:new Level");
	}

private:

	const std::string LEVEL_PATH = "Assets\\Level\\";
};