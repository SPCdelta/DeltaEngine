#include "MainMenuScene.hpp"
#include "../Scripts/TempAudio.hpp"
#include "Engine/Audio/MusicSource.hpp"
#include "Engine/Audio/SFXSource.hpp"
#include "../Views/MenuView.hpp"

MainMenuScene::MainMenuScene(const std::string& sceneName) 
	: Scene(sceneName)
{
	MenuView menuView { *this, "Main Menu", 4, "Assets\\Fonts\\knight_warrior.otf", {500, 100}, {300, 100}, 50, 80 };
	menuView.SetButtonText(0, "Start");
	menuView.SetButtonText(1, "Options");
	menuView.SetButtonText(2, "Dev");
	menuView.SetButtonText(3, "Quit");
	menuView.SetButtonTextPosition(0, {560, 100});
	menuView.SetButtonTextPosition(1, {525, 250});
	menuView.SetButtonTextPosition(2, {595, 400});
	menuView.SetButtonTextPosition(3, {580, 550});
	menuView.SetButtonOnLeftMouseClick(2, [this]() -> void 
		{
			LoadScene("DevScene");
		}, "Default");
}
