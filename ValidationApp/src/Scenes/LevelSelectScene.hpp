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
	static constexpr auto levelSettingsPath = "Assets\\Settings\\levels.json";
	static constexpr auto levelsPath = "Assets\\Level";

	LevelSelectScene(const std::string& name) : Scene(name)
	{ }

	void OnStart() override
	{
		// Title
		_title = CreateText("Select Level", "goblin", 32, Rendering::Color{ 255, 0, 0, 255 }).get();
		_title->transformRef.position = { 100.0f, 20.0f };
		_title->transformRef.scale = { 100.0f, 80.0f };

		// Background
		std::shared_ptr<GameObject> background = CreateImage("main_menu_bg", Layer::Background);
		background->transformRef.scale = { 1280.0f, 720.0f };

		// Refresh
		std::shared_ptr<GameObject> refreshButton = CreateButton("Refresh", "goblin", 32, Rendering::Color{ 255, 0, 0, 255}, Layer::Button);
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
		// Check files
		if (!FileManager::FileExists(levelSettingsPath))
		{
			std::vector<std::string> directoryFiles = FileManager::filesInDirectory(levelsPath);
			SaveLevelSettings(directoryFiles);
		}
			
		FileManager fileManager{};
		Json::json file = fileManager.Load(levelSettingsPath, "json");
		std::vector<std::string> existingFiles = FileManager::filesInDirectory(levelsPath);
		std::vector<std::string> toSave{};

		// Levels
		size_t buttonAmount{ 0 };
		for (size_t i = 0; i < file["levels"].size(); i++)
		{
			std::string levelName = file["levels"][i];

			// Check if Valid
			auto it = std::find(existingFiles.begin(), existingFiles.end(), levelName);
			if (it != existingFiles.end())
			{
				// Exists
				existingFiles.erase(it);
			}
			else
			{
				continue;
			}

			CreateLevelButton(buttonAmount, levelName, _title);

			toSave.push_back(levelName);

			buttonAmount++;
		}

		for (std::string& file : existingFiles)
		{
			CreateLevelButton(buttonAmount, file, _title);
			toSave.push_back(file);

			buttonAmount++;
		}

		SaveLevelSettings(toSave);
	}

	static std::string FormatDisplayName(const std::string& levelName)
	{
		std::string uhm = std::filesystem::path(levelName).stem().string();
		if (uhm.length() > 16)
		{
			return uhm.substr(0, 13) + "...";
		}
		return uhm;
	}

	static void SaveLevelSettings(std::vector<std::string>& files)
	{
		FileManager fileManager{};
		Json::json levelsJson;

		for (size_t i = 0; i < files.size(); ++i)
		{
			levelsJson["levels"][i] = files[i];
		}

		fileManager.Save(levelSettingsPath, "json", levelsJson);
	}

	void CreateLevelButton(size_t index, std::string levelName, GameObject* title)
	{
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