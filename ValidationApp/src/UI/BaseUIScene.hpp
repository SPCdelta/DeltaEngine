#pragma once

#include <Engine/Delta.hpp>

#include "UIFactory.hpp"

class BaseUIScene : public Scene
{
public:
	BaseUIScene(const std::string& name, const std::string& title, const std::string& previousSceneName) 
		: Scene(name),
		_titleText{ title }, _previousSceneName{ previousSceneName }
	{

	}

	void OnStart() override
	{
		// Background
		std::shared_ptr<GameObject> background = UIFactory::CreateImage(this, "main_menu_bg", Layer::Background);
		background->transformRef.scale = {1280.0f, 720.0f};
		background->transformRef.position = { 0.0f, 0.0f };
		background->AddComponent<Audio::MusicSource>("intro_theme", false, -1)->Play();

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

	Math::Vector2 GetContentOffset()
	{
		return { (1280.0f * 0.5f), SideMargin };
	}

	Math::Vector2 GetBarOffset()
	{
		return 
		{ 
			SideMargin, 
			(SideMargin + _title->transformRef.position.GetY() + _title->transformRef.scale.GetY() + SideMargin) 
		};
	}

private:
	static constexpr float SideMargin = 64.0f;

	std::string _titleText;
	std::string _previousSceneName;

	GameObject* _title = nullptr;
	GameObject* _backButton = nullptr;
};
