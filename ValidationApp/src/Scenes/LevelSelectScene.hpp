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
	{
		std::shared_ptr<GameObject> title = CreateText("Select Level", "goblin", 32, Rendering::Color{ 255, 0, 0, 255 });
		title->transformRef.position = { 100.0f, 100.0f };
		title->transformRef.scale = { 100.0f, 100.0f };

		for (int i = 0; i < _levels.size(); i++)
		{
			LevelUiData& levelUiData = _levels[i];
			std::shared_ptr<GameObject> buttonObj = CreateButton(levelUiData.displayName, "goblin", 16, Rendering::Color{255, 0, 0, 255});
			Ui::Button& button = buttonObj->GetComponent<Ui::Button>();
			button.SetOnLeftMouseClick(
				[this, levelUiData]() 
				{ 
					LevelSceneData* data = new LevelSceneData{ levelUiData.sceneName };
					LoadScene("LevelScene", data);
				},
				"jeroen"
			);
			buttonObj->transformRef.position = { 100.0f, (50.0f + 10.0f) * i + 200.0f  };
			buttonObj->transformRef.scale = { 100.0f, 50.0f };
			//button.SetPosition(buttonObj->transformRef.position);
			//button.SetScale(buttonObj->transformRef.scale);
		}
	}

protected:
	std::shared_ptr<GameObject> CreateText(const std::string& text, const std::string& font, int fontSize, const Rendering::Color color)
	{
		std::shared_ptr<GameObject> textObj = Instantiate();
		textObj->AddComponent<Ui::Text>(text, font, fontSize, color);
		return textObj;
	}

	std::shared_ptr<GameObject> CreateButton(const std::string& text, const std::string& font, int fontSize, const Rendering::Color textColor)
	{
		std::shared_ptr<GameObject> buttonObj = Instantiate();
		buttonObj->AddComponent<Ui::Button>(Vector2{ 100.0f, 100.0f }, Vector2{ 100.0f, 50.0f });
		buttonObj->AddComponent<Ui::Text>(text, font, fontSize, textColor);
		buttonObj->AddComponent<Ui::Image>("scroll3");
		return buttonObj;
	}

private:
	std::vector<LevelUiData> _levels
	{
		LevelUiData
		{
			"The Beginning",
			"level-1"
		},
		LevelUiData
		{
			"The Maze",
			"level-2"
		},
		LevelUiData
		{
			"Portals?",
			"level-3"
		}
	};
};