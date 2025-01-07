#pragma once

#include <Engine/Delta.hpp>

#include "LevelScene.hpp"

struct LevelUiData
{
	std::string displayName;
	std::string sceneName;
};

class LevelSelectScene : public Scene
{
public:
	LevelSelectScene(const std::string& name) : Scene(name)
	{ }

	void OnStart() override
	{
		// Title
		std::shared_ptr<GameObject> title = CreateText("Select Level", "goblin", 32, Rendering::Color{ 255, 0, 0, 255 });
		title->transformRef.position = { 100.0f, 20.0f };
		title->transformRef.scale = { 100.0f, 80.0f };

		// Background
		std::shared_ptr<GameObject> background = CreateImage("main_menu_bg", Layer::Background);
		background->transformRef.scale = { 1280.0f, 720.0f };

		// Check files
		const std::string levelSettingsPath = "Assets\\Settings\\levels.json";
		const std::string levelsPath = "Assets\\Level";
		if (!FileManager::FileExists(levelSettingsPath))
		{
			FileManager fileManager{};
			Json::json levelsJson;

			std::vector<std::string> directoryFiles = FileManager::filesInDirectory(levelsPath);
			for (size_t i = 0; i < directoryFiles.size(); ++i)
			{
				levelsJson["levels"][i] = directoryFiles[i];
			}

			fileManager.Save(levelSettingsPath, "json", levelsJson);
		}
			
		FileManager fileManager{};
		Json::json file = fileManager.Load(levelSettingsPath, "json");

		// Levels
		for (size_t i = 0; i < file["levels"].size(); i++)
		{
			std::string levelName = file["levels"][i];
			std::string displayName = FormatDisplayName(levelName);

			std::shared_ptr<GameObject> buttonObj = CreateButton(displayName, "goblin", 16, Rendering::Color{255, 0, 0, 255}, Layer::Button);
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
				100.0f, (50.0f + 10.0f) * i +
							(title->transformRef.position.GetY() +
							 title->transformRef.scale.GetY() + 20.0f)};

			float xSize = (Font::GetFontSize(text.GetFont(), text.GetText()).GetX() * 1.25f);
			buttonObj->transformRef.scale = 
			{ 
				xSize, 
				50.0f
			};
			text.SetPosition({ (buttonObj->transformRef.scale.GetX() - xSize) * 0.5f, 0.0f });
		}
	}

protected:
	std::shared_ptr<GameObject> CreateText(const std::string& text, const std::string& font, int fontSize, const Rendering::Color color)
	{
		std::shared_ptr<GameObject> textObj = Instantiate();
		textObj->AddComponent<Ui::Text>(text, font, fontSize, color);
		return textObj;
	}

	std::shared_ptr<GameObject> CreateButton(const std::string& text, const std::string& font, int fontSize, const Rendering::Color textColor, Layer layer)
	{
		std::shared_ptr<GameObject> buttonObj = Instantiate();
		buttonObj->AddComponent<Ui::Button>(Vector2{ 100.0f, 100.0f }, Vector2{ 100.0f, 50.0f });
		buttonObj->AddComponent<Ui::Text>(text, font, fontSize, textColor);
		buttonObj->AddComponent<Ui::Image>("scroll3")->SetLayer(layer);
		return buttonObj;
	}

	std::shared_ptr<GameObject> CreateImage(const std::string& spriteName, Layer layer)
	{
		std::shared_ptr<GameObject> imageObj = Instantiate();
		imageObj->AddComponent<Ui::Image>(spriteName)->SetLayer(layer);
		return imageObj;
	}

private:
	static std::string FormatDisplayName(const std::string& levelName)
	{
		if (levelName.length() > 16)
		{
			return levelName.substr(0, 13) + "...";
		}
		return levelName;
	}
};