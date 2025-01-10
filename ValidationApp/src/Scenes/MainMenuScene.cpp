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
	BaseUIScene::OnStart();

	std::shared_ptr<GameObject> selectLevelButton = UIFactory::CreateButton(this, "Start!", "goblin", 24, Rendering::Color{255, 255, 255, 255}, Layer::Button);
	selectLevelButton->transformRef.position += (GetContentOffset() + Math::Vector2{ 0.0f, 75.0f * 0.0f });
	selectLevelButton->GetComponent<Ui::Button>().SetOnLeftMouseClick([this](){ LoadScene("LevelSelectScene"); }, "UI");

	std::shared_ptr<GameObject> levelEditorButton = UIFactory::CreateButton(this, "Level Editor", "goblin", 24, Rendering::Color{255, 255, 255, 255}, Layer::Button);
	levelEditorButton->transformRef.position += (GetContentOffset() + Math::Vector2{ 0.0f, 75.0f * 1.0f });
	levelEditorButton->GetComponent<Ui::Button>().SetOnLeftMouseClick([this](){ LoadScene("LevelEditorMenuScene"); }, "UI");

	std::shared_ptr<GameObject> quitButton = UIFactory::CreateButton(this, "Quit", "goblin", 24, Rendering::Color{ 255, 255, 255, 255 }, Layer::Button);
	quitButton->transformRef.position += (GetContentOffset() + Math::Vector2{ 0.0f, 75.0f * 2.0f });
	quitButton->GetComponent<Ui::Button>().SetOnLeftMouseClick([this](){ Application::Quit(); }, "UI");
	
#ifdef _DEBUG
	std::shared_ptr<GameObject> devButton = UIFactory::CreateButton(this, "Dev", "goblin", 24, Rendering::Color{255, 255, 255, 255}, Layer::Button);
	devButton->transformRef.position += (GetContentOffset() + Math::Vector2{ 0.0f, 75.0f * 3.0f });
	devButton->GetComponent<Ui::Button>().SetOnLeftMouseClick([this](){ LoadScene("DevScene"); }, "UI");
#endif
}
