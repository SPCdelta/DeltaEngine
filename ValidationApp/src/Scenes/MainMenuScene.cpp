#include "MainMenuScene.hpp"

#include <memory>

#include "Engine/Audio/MusicSource.hpp"
#include "Engine/Audio/SFXSource.hpp"
#include "../Views/MenuView.hpp"

MainMenuScene::MainMenuScene(const std::string& sceneName) 
	: BaseUIScene(sceneName, "Main Menu", "None")
{

}

void MainMenuScene::OnStart() 
{
	/*// Other
	MenuView menuView 
	{ 
		*this, "Main Menu", 
	#if _DEBUG
		4, 
	#else
		3,
	#endif
		"alucrads", 
		{485, 50}, 
		{300, 100}, 
		25, 
		80 
	};*/ //TODO from merge ?
	BaseUIScene::OnStart();

	std::shared_ptr<GameObject> selectLevelButton = UIFactory::CreateButton(this, "Start!", "goblin", 24, Rendering::Color{255, 255, 255, 255}, Layer::Button);
	selectLevelButton->transformRef.position += (GetContentOffset() + Math::Vector2{ 0.0f, 75.0f * 0.0f });
	selectLevelButton->GetComponent<Ui::Button>().SetOnLeftMouseClick([this](){ LoadScene("LevelSelectScene"); }, "UI");

	/*auto& music = menu->GetComponent<Audio::MusicSource>();
	music.SetVolume(20);

	menuView.SetTitleTextPosition({515, 50});
	menuView.SetTitleTextColor({255, 255, 255, 255});*/ // TODO from merge?

	std::shared_ptr<GameObject> levelEditorButton = UIFactory::CreateButton(this, "Level Editor", "goblin", 24, Rendering::Color{255, 255, 255, 255}, Layer::Button);
	levelEditorButton->transformRef.position += (GetContentOffset() + Math::Vector2{ 0.0f, 75.0f * 1.0f });
	levelEditorButton->GetComponent<Ui::Button>().SetOnLeftMouseClick([this](){ LoadScene("LevelEditorMenuScene"); }, "UI");

	std::shared_ptr<GameObject> quitButton = UIFactory::CreateButton(this, "Quit", "goblin", 24, Rendering::Color{ 255, 255, 255, 255 }, Layer::Button);
	quitButton->transformRef.position += (GetContentOffset() + Math::Vector2{ 0.0f, 75.0f * 2.0f });
	quitButton->GetComponent<Ui::Button>().SetOnLeftMouseClick([this](){ Application::Quit(); }, "UI");

	/*menuView.SetButtonPosition(0, {435, 175});
	menuView.SetButtonScale(0, {400, 100});

	menuView.SetButtonPosition(1, { 435, 300 });
	menuView.SetButtonScale(1, { 400, 100 });

	menuView.SetButtonTextSize(1, 60);

	menuView.SetButtonText(0, "Start");
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

	menuView.SetButtonOnLeftMouseClickLoadScene(1, this, "LevelEditorLevelChose", "Level Editor");
	menuView.SetButtonSFX(-1, "button_1_click");

	auto& sfx = menuView.GetButton(0)->GetComponent<Audio::SFXSource>();
	menuView.SetButtonOnLeftMouseClick(-1, [&sfx]() -> void
	{
		sfx.Play();
	}, "Main Menu");
	sfx.SetVolume(20);*/ // TODO from merge?
	
#ifdef _DEBUG
	std::shared_ptr<GameObject> devButton = UIFactory::CreateButton(this, "Dev", "goblin", 24, Rendering::Color{255, 255, 255, 255}, Layer::Button);
	devButton->transformRef.position += (GetContentOffset() + Math::Vector2{ 0.0f, 75.0f * 3.0f });
	devButton->GetComponent<Ui::Button>().SetOnLeftMouseClick([this](){ LoadScene("DevScene"); }, "UI");
#endif
}
