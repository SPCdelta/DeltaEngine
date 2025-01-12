#include "LevelSelectScene.hpp"

LevelSelectScene::LevelSelectScene(const std::string& name)
	: BaseUIScene(name, "Start", "MainMenuScene")
{
}

void LevelSelectScene::OnStart()
{
	BaseUIScene::OnStart();
	CreateLevelsList();
}

void LevelSelectScene::Refresh() 
{
	for (GameObject* button : _buttons)
		button->Destroy();
	_buttons.clear();
	CreateLevelsList();
}

void LevelSelectScene::CreateLevelsList()
{
	std::vector<std::string> levels{};
	LevelManager::GetLevels(levels, true);

	for (size_t i = 0; i < levels.size(); i++)
		CreateLevelButton(i, levels[i]);
}

void LevelSelectScene::CreateLevelButton(size_t index, std::string levelName)
{
	std::string displayName = LevelManager::FormatDisplayName(levelName);

	std::shared_ptr<GameObject> buttonObj = UIFactory::CreateButton(this, displayName, "goblin", 16, Rendering::Color{255, 255, 255, 255}, Layer::Button);
	Ui::Button& button = buttonObj->GetComponent<Ui::Button>();
	Ui::Text& text = buttonObj->GetComponent<Ui::Text>();

	button.SetOnLeftMouseClick
	(
		[this, levelName]()
		{ 
			Json::json jsonLevelName;
			jsonLevelName["levelName"] = levelName;
			StoreUserData(jsonLevelName);

			LoadScene("WeaponSelectionScene");
		},
		"LevelSelect"
	);
	buttonObj->transformRef.position = Math::Vector2{ 100.0f, (50.0f + 10.0f) * index } + GetContentOffset();

	float xSize = (Font::GetFontSize(text.GetFont(), text.GetText()).GetX() * 1.25f);
	_buttons.push_back(buttonObj.get());
}