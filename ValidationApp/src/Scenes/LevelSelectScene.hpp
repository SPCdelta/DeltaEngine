#pragma once

#include "../Classes/LevelManager.hpp"
#include "LevelScene.hpp"
#include "../UI/UIFactory.hpp"

class LevelSelectScene : public Scene
{
public:
	LevelSelectScene(const std::string& name) : Scene(name)
	{ }

	void OnStart() override
	{
		// Title
		_title = UIFactory::CreateText(this, "Select Level", "goblin", 32, Rendering::Color{ 255, 0, 0, 255 }).get();
		_title->transformRef.position = { 100.0f, 20.0f };
		_title->transformRef.scale = { 100.0f, 80.0f };

		// Background
		std::shared_ptr<GameObject> background = UIFactory::CreateImage(this, "main_menu_bg", Layer::Background);
		background->transformRef.scale = { 1280.0f, 720.0f };

		// Refresh
		std::shared_ptr<GameObject> refreshButton = UIFactory::CreateButton(this, "Refresh", "goblin", 32, Rendering::Color{ 255, 0, 0, 255}, Layer::Button);
		refreshButton->transformRef.position = { 0.0f, 0.0f };
		refreshButton->transformRef.scale = { 100.0f, 50.0f };
		refreshButton->GetComponent<Ui::Button>().SetOnLeftMouseClick(
			[this]() 
			{
				std::cout << "Meow!" << std::endl;
				Refresh();
			},
			"jeroen"
		);

		// 
		CreateLevelsList();
	}

private:
	std::vector<GameObject*> _buttons;
	GameObject* _title = nullptr;

	void Refresh() 
	{
		for (GameObject* button : _buttons)
		{
			DestroyObject(button);
		}
		_buttons.clear();

		CreateLevelsList();
	}

	void CreateLevelsList()
	{
		std::vector<std::string> levels{};
		LevelManager::GetLevels(levels, true);

		for (size_t i = 0; i < levels.size(); i++)
		{
			CreateLevelButton(i, levels[i], _title);
		}
	}

	void CreateLevelButton(size_t index, std::string levelName, GameObject* title)
	{
		std::string displayName = LevelManager::FormatDisplayName(levelName);

		std::shared_ptr<GameObject> buttonObj = UIFactory::CreateButton(this, displayName, "goblin", 16, Rendering::Color{255, 0, 0, 255}, Layer::Button);
		Ui::Button& button = buttonObj->GetComponent<Ui::Button>();
		Ui::Text& text = buttonObj->GetComponent<Ui::Text>();
		button.SetOnLeftMouseClick(
			[this, levelName]()
			{ 
				Json::json jsonLevelName;
				jsonLevelName["levelName"] = levelName;
				StoreUserData(jsonLevelName);

				LoadScene("LevelScene");
			},
			"jeroen"
		);
		buttonObj->transformRef.position = {
			100.0f, (50.0f + 10.0f) * index +
						(title->transformRef.position.GetY() +
						 title->transformRef.scale.GetY() + 20.0f)};

		float xSize = (Font::GetFontSize(text.GetFont(), text.GetText()).GetX() * 1.25f);
		buttonObj->transformRef.scale = 
		{ 
			xSize, 
			50.0f
		};
		text.SetPosition({ (buttonObj->transformRef.scale.GetX() - xSize) * 0.5f, 0.0f });
		_buttons.push_back(buttonObj.get());
	}
};