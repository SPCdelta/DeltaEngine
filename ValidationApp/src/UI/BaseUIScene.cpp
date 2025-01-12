#include "BaseUIScene.hpp"

BaseUIScene::BaseUIScene(const std::string& name, const std::string& title, const std::string& previousSceneName) 
	: Scene(name),
	  _titleText{ title }, 
	  _previousSceneName{ previousSceneName }
{

}

void BaseUIScene::OnStart()
{
	// Background
	std::shared_ptr<GameObject> background = UIFactory::CreateImage(this, "main_menu_bg", Layer::Background);
	background->transformRef.scale = {1280.0f, 720.0f};
	background->transformRef.position = { 0.0f, 0.0f };
	background->AddComponent<Audio::MusicSource>("intro_theme", false, -1)->Play();

	auto& music = background->GetComponent<Audio::MusicSource>();
	music.SetVolume(20);

	// Title
	_title = UIFactory::CreateText(this, _titleText, "goblin", 32, Rendering::Color{ 255, 255, 255, 255 }).get();
	_title->transformRef.position = { SideMargin, SideMargin };

	// Back
	if (_previousSceneName != "None")
	{
		_backButton = UIFactory::CreateButton(this, "Back", "goblin", 24, Rendering::Color{ 255, 255, 255, 255 }, Layer::Button).get();
		_backButton->transformRef.position = { SideMargin, 720.0f - 50.0f - SideMargin };
		_backButton->GetComponent<Ui::Button>().SetOnLeftMouseClick([this]() { LoadScene(_previousSceneName); }, "UI");
	}
}

Math::Vector2 BaseUIScene::GetContentOffset()
{
	return { (1280.0f * 0.5f), SideMargin };
}

Math::Vector2 BaseUIScene::GetBarOffset()
{
	return 
	{ 
		SideMargin, 
		(SideMargin + _title->transformRef.position.GetY() + _title->transformRef.scale.GetY() + SideMargin) 
	};
}