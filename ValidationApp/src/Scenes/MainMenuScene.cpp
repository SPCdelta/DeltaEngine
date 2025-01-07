#include "MainMenuScene.hpp"

#include <memory>

#include "../Scripts/TempAudio.hpp"
#include "Engine/Audio/MusicSource.hpp"
#include "Engine/Audio/SFXSource.hpp"
#include "../Views/MenuView.hpp"
#include "../Classes/MySceneData.hpp"

MainMenuScene::MainMenuScene(const std::string& sceneName) 
	: Scene(sceneName)
{

}

void MainMenuScene::OnStart() 
{
	// Other
	MenuView menuView { *this, "Main Menu",
		#if _DEBUG
		4, 
		#else
		3,
		#endif
		"alucrads", {485, 50}, {300, 100}, 25, 80 };

	std::shared_ptr<GameObject> menu{ Instantiate({{0.0f, 0.0f}, 0.0f, {1280.0f, 720.0f}}) };
	menu->AddComponent<Ui::Image>("main_menu_bg");
	menu->AddComponent<Audio::MusicSource>("intro_theme", false, true)->Play();

	menuView.SetTitleTextPosition({515, 50});
	menuView.SetTitleTextColor({255, 255, 255, 255});

	menuView.SetButtonTexture(0, "scroll2");
	menuView.SetButtonTextColor(-1, {255, 255, 255, 255});
	menuView.SetButtonTexture(1, "scroll2");

	menuView.SetButtonPosition(0, {435, 175});
	menuView.SetButtonScale(0, {400, 100});

	menuView.SetButtonPosition(1, { 435, 300 });
	menuView.SetButtonScale(1, { 400, 100 });

	menuView.SetButtonTextSize(1, 60);

	menuView.SetButtonText(0, "Start");
	menuView.SetButtonOnLeftMouseClickLoadScene(0, this, "LevelSelectScene", "Main Menu");

	menuView.SetButtonText(1, "Level Editor");
	menuView.SetButtonText(2, "Quit");

	menuView.AddButtonTextPosition(-1, {65, 15});
	menuView.AddButtonTextPosition(0, {15, 0});
	menuView.AddButtonTextPosition(1, {-20, 10});
	menuView.AddButtonTextPosition(2, {40, 0});
#if _DEBUG
	menuView.SetButtonText(3, "Dev");
	menuView.AddButtonTextPosition(3, {45, 0});
	menuView.SetButtonOnLeftMouseClickLoadScene(3, this, "DevScene", "Main Menu");
#endif
	menuView.SetButtonOnLeftMouseClickLoadScene(1, this, "LevelEditorMenuScene", "Level Editor");
	menuView.SetButtonSFX(-1, "button_1_click");

	auto& sfx = menuView.GetButton(0)->GetComponent<Audio::SFXSource>();
	menuView.SetButtonOnLeftMouseClick(-1, [&sfx]() -> void
		{
			sfx.Play();
		}, "Main Menu");
	sfx.SetVolume(20);

	// TODO: Input blijkt deze functie nooit op te ruimen? Zie Ui::Button destructor.
	//menuView.SetButtonOnLeftMouseClick(3, [this]() -> void
	//	{
	//		this->GetWindow()->Close();
	//	}, "Main Menu");
}
