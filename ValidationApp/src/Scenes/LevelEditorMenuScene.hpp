#pragma once

#include "Engine/Delta.hpp"
#include "../UI/BaseUIScene.hpp"
#include "../Classes/LevelManager.hpp"

struct LevelButton
{
	GameObject* deleteButton{ nullptr };
	GameObject* levelButton{ nullptr };
	GameObject* backwardsButton{ nullptr };
	GameObject* forwardsButton{ nullptr };
	size_t index{ 0 };
};

class LevelEditorMenuScene : public BaseUIScene
{
public:
	LevelEditorMenuScene(const std::string& name);

	void OnStart() override;

	void SelectLevel(const std::string& level);
	void DeleteLevel(const std::string& level);

	void MoveLevelForwards(const std::string& levelName);
	void MoveLevelBackwards(const std::string& levelName);

	void Refresh();

private:
	static constexpr float SelectLevelButtonWidth = 300.0f;
	static constexpr float ButtonHeight = 50.0f;
	static constexpr float Margin = 10.0f;

	std::unordered_map<std::string, LevelButton> _buttons{};
	std::vector<LevelButton> _buttonsPool{};
	std::vector<std::string> _order{};

	void CreateCRUDButtons();
	void CreateLevelButtons();
	void CreateLevelButton(size_t index, const std::string& name);
	void DestroyLevelButton(LevelButton& levelButton);
	void UpdateLevelButton(const std::string& levelName);

	const std::string LEVEL_PATH = "Assets\\Level\\";
};