#include "MainMenuScene.hpp"
#include "../Scripts/TempAudio.hpp"
#include "Engine/Audio/MusicSource.hpp"
#include "Engine/Audio/SFXSource.hpp"
#include "../Views/MenuView.hpp"
#include <memory>

MainMenuScene::MainMenuScene(const std::string& sceneName) 
	: Scene(sceneName)
{
	MenuView menuView { *this, "Main Menu", 4, "alucrads", {500, 50}, {300, 100}, 25, 80 };

	std::shared_ptr<GameObject> bgImage{ Instantiate({{0.0f, 0.0f}, 0.0f, {1280.0f, 720.0f}}) };
	bgImage->AddComponent<Ui::Image>("main_menu_bg");

	menuView.SetTitleTextPosition({475, 50});
	menuView.SetTitleTextColor({255, 255, 255, 255});

	menuView.SetButtonTexture(0, "scroll2");
	menuView.SetButtonTextColor(-1, {255, 255, 255, 255});
	menuView.SetButtonTextSize(-1, 100);

	menuView.SetButtonPosition(0, {450, 175});
	menuView.SetButtonScale(0, {400, 100});

	menuView.SetButtonText(0, "Start");
	menuView.SetButtonText(1, "Options");
	menuView.SetButtonText(2, "Dev");
	menuView.SetButtonText(3, "Quit");
	menuView.SetButtonTextPosition(0, {560, 175});
	menuView.SetButtonTextPosition(1, {525, 300});
	menuView.SetButtonTextPosition(2, {595, 425});
	menuView.SetButtonTextPosition(3, {580, 550});
	menuView.SetButtonOnLeftMouseClickLoadScene(2, *this, "DevScene", "Main Menu");
	menuView.SetButtonSFX(-1, "Assets\\Audio\\SFX\\Button_1.mp3");

	auto& sfx = menuView.GetButton(0)->GetComponent<Audio::SFXSource>();
	menuView.SetButtonOnLeftMouseClick(-1, [&sfx]() -> void
		{
			sfx.Play();
		}, "Main Menu");
	sfx.SetVolume(20);

	menuView.SetButtonOnLeftMouseClick(3, [this]() -> void
		{
			this->GetWindow()->Close();
		}, "Main Menu");
}
