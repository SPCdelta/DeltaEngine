#pragma once

#include "../UI/BaseUIScene.hpp"

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
	LevelEditorMenuScene(const std::string& name) 
		: BaseUIScene(name, "Level Editor", "MainMenuScene")
	{

	}

	void OnStart() override
	{ 
		BaseUIScene::OnStart();
		CreateCRUDButtons();
		CreateLevelButtons();
	}

	void SelectLevel(const std::string& level)
	{
		Json::json jsonLevelName;
		jsonLevelName["levelName"] = level;
		StoreUserData(jsonLevelName);

		LoadScene("LevelEditor");
	}

	void DeleteLevel(const std::string& level)
	{
		auto it = _buttons.find(level);
		if (it == _buttons.end())
		{
			Refresh();
			return;
		}

		DestroyLevelButton(it->second);
		_order.erase(std::remove(_order.begin(), _order.end(), level), _order.end());
		if (_buttons.contains(level))
		{
			_buttons.erase(level);
		}

		LevelManager::SaveLevelSettings(_order);
	}

	void MoveLevelForwards(const std::string& levelName)
	{
		// Decrease | - (Closer to 0)
		for (size_t i = 0; i < _order.size(); i++)
		{
			if (_order[i] != levelName)
				continue;

			// If its first do nothing
			if (i == 0)
				break;

			std::string previous = _order[i - 1];
			_order[i - 1] = levelName;
			_order[i] = previous;

			// Change Position
			_buttons[levelName].index -= 1;
			_buttons[previous].index += 1;

			// 1 2 3 4 5
			// - - C - - found current
			// - P - - - copy previous
			// - C - - - set previous to current
			// - C P - - set current to copy of previous

			UpdateLevelButton(previous);
			UpdateLevelButton(levelName);
			LevelManager::SaveLevelSettings(_order);

			break;
		}
	}

	void MoveLevelBackwards(const std::string& levelName)
	{
		// Increase | + (Further from 0)
		for (size_t i = 0; i < _order.size(); i++)
		{
			if (_order[i] != levelName)
				continue;

			// If its last do nothing
			if (i == _order.size() - 1)
				break;

			std::string next = _order[i + 1];
			_order[i + 1] = levelName;
			_order[i] = next;

			// Change Position
			_buttons[levelName].index += 1;
			_buttons[next].index -= 1;

			// 1 2 3 4 5
			// - - C - - found current
			// - - - N - copy next
			// - - - C - set next to current
			// - - N C - set current to copy of next

			UpdateLevelButton(next);
			UpdateLevelButton(levelName);
			LevelManager::SaveLevelSettings(_order);

			break;
		}
	}

	void Refresh()
	{

	}

private:
	static constexpr float SelectLevelButtonWidth = 300.0f;
	static constexpr float ButtonHeight = 50.0f;
	static constexpr float Margin = 10.0f;

	std::unordered_map<std::string, LevelButton> _buttons{};
	std::vector<std::string> _order{};

	void CreateCRUDButtons()
	{
		std::shared_ptr<GameObject> createLevelButton = UIFactory::CreateButton(
			this, "Create new level", "goblin", 24, Rendering::Color{ 255, 255, 255, 255 },
			Layer::Button);
		createLevelButton->transformRef.position += Math::Vector2{50, 150} + Math::Vector2{ 0.0f, 75.0f * 0.0f };

		std::shared_ptr<GameObject> shareLevelButton = UIFactory::CreateButton(
			this, "Share levels", "goblin", 24, Rendering::Color{ 255, 255, 255, 255 },
			Layer::Button);
		shareLevelButton->transformRef.position += Math::Vector2{ 50, 150 } + Math::Vector2{ 0.0f, 75.0f * 1.0f };
		shareLevelButton->GetComponent<Ui::Button>().SetOnLeftMouseClick([this]() -> void
			{
				fs::path fullPath = fs::absolute(LEVEL_PATH);
				fs::path currentPath = fs::current_path();
				fs::path relativePath = fs::relative(fullPath, currentPath);
				system(std::string{ "explorer " + relativePath.string() }.c_str());
			}, "UI");
	}

	void CreateLevelButtons()
	{
		std::vector<std::string> levels{};
		LevelManager::GetLevels(levels, true);

		for (size_t i = 0; i < levels.size(); i++)
		{
			_order.push_back(levels[i]);
			CreateLevelButton(i, levels[i]);
		}
	}

	void CreateLevelButton(size_t index, const std::string& name)
	{
		std::shared_ptr<GameObject> deleteButtonObj = UIFactory::CreateButton(this, 
			"X", "goblin", 16, Rendering::Color{255, 255, 255, 255}, Layer::Button);
		deleteButtonObj->GetComponent<Ui::Button>().SetOnLeftMouseClick(
			[this, name]() { DeleteLevel(name); }, "UI");
		deleteButtonObj->transformRef.scale = { ButtonHeight, ButtonHeight };
		deleteButtonObj->transformRef.position = Math::Vector2{ 0.0f, (ButtonHeight + Margin) * index } + GetContentOffset();

		std::shared_ptr<GameObject> selectLevelButtonObj = UIFactory::CreateButton(this, 
			LevelManager::FormatDisplayName(name), "goblin", 16,
			Rendering::Color{255, 255, 255, 255}, Layer::Button);
		selectLevelButtonObj->GetComponent<Ui::Button>().SetOnLeftMouseClick(
			[this, name]() { SelectLevel(name); }, "UI");
		selectLevelButtonObj->transformRef.scale = { SelectLevelButtonWidth, 50.0f };
		selectLevelButtonObj->transformRef.position = Math::Vector2{ (ButtonHeight + Margin), (ButtonHeight + Margin) * index } + GetContentOffset();

		std::shared_ptr<GameObject> decreaseLevelButtonObj = UIFactory::CreateButton(this,
			"V", "goblin", 16, Rendering::Color{255, 255, 255, 255}, Layer::Button);
		decreaseLevelButtonObj->GetComponent<Ui::Button>().SetOnLeftMouseClick(
			[this, name]() { MoveLevelBackwards(name); }, "UI");
		decreaseLevelButtonObj->transformRef.scale = { ButtonHeight, ButtonHeight };
		decreaseLevelButtonObj->transformRef.position = Math::Vector2{ ((ButtonHeight + SelectLevelButtonWidth) + (Margin * 2)), (ButtonHeight + Margin) * index } + GetContentOffset();

		std::shared_ptr<GameObject> increaseLevelButtonObj = UIFactory::CreateButton(this, 
			"^", "goblin", 16, Rendering::Color{255, 255, 255, 255}, Layer::Button);
		increaseLevelButtonObj->GetComponent<Ui::Button>().SetOnLeftMouseClick(
			[this, name]() { MoveLevelForwards(name); }, "UI");
		increaseLevelButtonObj->transformRef.scale = { ButtonHeight, ButtonHeight };
		increaseLevelButtonObj->transformRef.position = Math::Vector2{ (((ButtonHeight * 2) + SelectLevelButtonWidth) + (Margin * 3)), (ButtonHeight + Margin) * index } + GetContentOffset();

		_buttons[name] = 
		{ 
			deleteButtonObj.get(),
			selectLevelButtonObj.get(),
			decreaseLevelButtonObj.get(),
			increaseLevelButtonObj.get(),
			index,
		};
	}

	void DestroyLevelButton(LevelButton& levelButton)
	{
		DestroyObject(levelButton.deleteButton);
		DestroyObject(levelButton.levelButton);
		DestroyObject(levelButton.backwardsButton);
		DestroyObject(levelButton.forwardsButton);
	}

	void UpdateLevelButton(const std::string& levelName)
	{
		LevelButton& levelButton = _buttons[levelName];
		float newY = ((ButtonHeight + Margin) * levelButton.index) + GetContentOffset().GetY();

		levelButton.deleteButton->transformRef.position.SetY(newY);
		levelButton.levelButton->transformRef.position.SetY(newY);
		levelButton.backwardsButton->transformRef.position.SetY(newY);
		levelButton.forwardsButton->transformRef.position.SetY(newY);
	}

	const std::string LEVEL_PATH = "Assets\\Level\\";
};