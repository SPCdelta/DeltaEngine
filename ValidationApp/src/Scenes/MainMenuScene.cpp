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
			InputManager::deactivateCategory("Main Menu");
			LoadScene("DevScene");
		}, "Main Menu");
	menuView.SetButtonSFX(-1, "Assets\\Audio\\SFX\\Button_1.mp3");

	/* 
	* Audio afspelen bij drukken van knop is heel inconsistent op dit moment
	* Het toevoegen van een functie aan een input is LIFO waardoor alles crasht omdat er eerst van scene wordt geswitched en dan alle audio afgespeeld wordt terwijl die al opgeruimd is.
	*/
	auto& sfx = menuView.GetButton(0)->GetComponent<Audio::SFXSource>();
	menuView.SetButtonOnLeftMouseClick(-1, [&sfx]() -> void
		{
			sfx.Play();
		}, "Main Menu");
}
